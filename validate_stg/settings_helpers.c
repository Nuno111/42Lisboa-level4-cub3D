/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stg_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:21:32 by ngregori          #+#    #+#             */
/*   Updated: 2021/04/22 12:55:39 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_string(char *str)
{
	int	i;
	int	num;
	int	comma;

	if (!str)
		return (false);
	i = 0;
	num = 0;
	comma = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num++;
		else if (str[i] == ',' && num <= 3)
		{
			comma++;
			num = 0;
		}
		else if (str[i] == ',')
			return (false);
		if (comma > 2 || num > 3 || (!ft_isdigit(str[i]) && str[i] != ','))
			return (false);
		i++;
	}
	return (true);
}

void	free_stg(t_scene *stg)
{
	if (stg->no)
		free(stg->no);
	if (stg->so)
		free(stg->so);
	if (stg->we)
		free(stg->we);
	if (stg->ea)
		free(stg->ea);
	if (stg->sprite)
		free(stg->sprite);
	if (stg->floor)
		free(stg->floor);
	if (stg->ceil)
		free(stg->ceil);
	if (stg->tmp_map)
		ft_free_list(&stg->tmp_map);
	if (stg->map)
		ft_freearrays(stg->map);
	if (stg->line)
		free(stg->line);
}

void	validate_floor_ceil2(t_scene *stg,
	t_color **floor_or_ceil, char **tmp_strs)
{
	t_color	*tmp;

	tmp = NULL;
	if (ft_str_is_numeric(tmp_strs[0]) && ft_str_is_numeric(tmp_strs[1])
		&& ft_str_is_numeric(tmp_strs[2]))
		tmp = malloc(sizeof(t_color));
	if (tmp)
	{
		tmp->r = ft_atoi(tmp_strs[0]);
		tmp->g = ft_atoi(tmp_strs[1]);
		tmp->b = ft_atoi(tmp_strs[2]);
		if (tmp->r >= 0 && tmp->r <= 255 && tmp->g >= 0 && tmp->g <= 255
			&& tmp->b >= 0 && tmp->b <= 255)
			*floor_or_ceil = tmp;
		else
			error_and_exit_stg(stg, "Error\nValues must be between 0 and 255");
	}
	else
		error_and_exit_stg(stg, "Error\nInvalid string format.");
}

double	deg_to_rad(int deg)
{
	return ((deg * M_PI) / 180.0);
}
