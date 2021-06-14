/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:09:52 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 16:43:40 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	get_max_width(t_scene *stg)
{
	int		i;
	size_t	curr_width;

	i = 0;
	while (stg->map[i])
	{
		curr_width = ft_strlen(stg->map[i]);
		if (curr_width > stg->map_width)
			stg->map_width = curr_width;
		i++;
	}
}

static	void	adjust_line_to_width(t_scene *stg)
{
	size_t	i;
	int		diff;

	i = 0;
	while (stg->map[i])
	{
		diff = stg->map_width - ft_strlen(stg->map[i]);
		while (diff > 0)
		{
			ft_add_letter(' ', &stg->map[i], false);
			diff--;
		}
		i++;
	}
	i = 0;
	while (stg->map[i])
	{
		ft_add_letter('+', &stg->map[i], true);
		ft_add_letter('+', &stg->map[i], false);
		i++;
	}
}

static	void	create_fake_line(t_scene *stg, char **fake_map, int i)
{
	fake_map[i] = malloc(sizeof(char) * (stg->map_width + 1));
	if (!fake_map[i])
		error_and_exit_stg(stg, "Error\nProblem allocating memory for the map.");
	ft_memset(fake_map[i], '+', stg->map_width);
	fake_map[i][stg->map_width] = '\0';
}

static	void	finish_fake_map(t_scene *stg, char **fake_map)
{
	size_t	i;

	get_max_width(stg);
	create_fake_line(stg, fake_map, 0);
	create_fake_line(stg, fake_map, stg->map_size + 1);
	fake_map[stg->map_size + 2] = NULL;
	i = 0;
	while (stg->map[i])
	{
		fake_map[i + 1] = ft_strdup(stg->map[i]);
		i++;
	}
}

void	create_fake_map(t_scene *stg)
{
	char		**fake_map;

	get_max_width(stg);
	adjust_line_to_width(stg);
	while (stg->map[stg->map_size])
		(stg->map_size)++;
	if (stg->map_size == 0)
		error_and_exit_stg(stg, "Error\nMap doesn't exist.");
	fake_map = malloc(sizeof(char *) * (stg->map_size + 3));
	if (!fake_map)
		error_and_exit_stg(stg, "Error\nProblem allocating memory for the map.");
	finish_fake_map(stg, fake_map);
	ft_freearrays(stg->map);
	stg->map = fake_map;
	while (stg->map[stg->map_size])
		stg->map_size++;
}
