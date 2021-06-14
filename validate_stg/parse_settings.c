/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:20:30 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 16:53:38 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	char	*remove_spaces(char **line)
{
	int		i;
	char	*new;

	new = NULL;
	i = 1;
	while (line[0][i])
	{
		if (line[0][i] != ' ')
			ft_add_letter(line[0][i], &new, false);
		i++;
	}
	return (new);
}

static	void	parse_map(char *line, t_scene *stg)
{
	int		i;
	char	*valid;
	t_list	*node;

	i = 0;
	while (line[i])
	{
		valid = ft_strchr("012NSEW\t ", line[i]);
		if (!valid)
			break ;
		i++;
	}
	if (valid)
	{
		node = ft_lstnew(ft_strdup(line));
		ft_lstadd_back(&stg->tmp_map, node);
	}
	else
		error_and_exit_stg(stg, "Error\nForbidden character found.");
}

static	void	verify_identifiers(char **strs, t_scene *stg)
{
	char	*identifier;

	identifier = strs[0];
	if (!identifier || !strs[1])
		error_and_exit_stg(stg, "Error\nProblem found when handling paths.");
	if (ft_strcmp(identifier, "R") == 0)
		validate_r(stg, strs);
	else if (ft_strcmp(identifier, "NO") == 0)
		validate_textures(stg, &stg->no, strs);
	else if (ft_strcmp(identifier, "SO") == 0)
		validate_textures(stg, &stg->so, strs);
	else if (ft_strcmp(identifier, "EA") == 0)
		validate_textures(stg, &stg->ea, strs);
	else if (ft_strcmp(identifier, "WE") == 0)
		validate_textures(stg, &stg->we, strs);
	else if (ft_strcmp(identifier, "S") == 0)
		validate_textures(stg, &stg->sprite, strs);
	else if (ft_strcmp(identifier, "F") == 0)
		validate_floor_ceil(stg, &stg->floor, strs);
	else if (ft_strcmp(identifier, "C") == 0)
		validate_floor_ceil(stg, &stg->ceil, strs);
	else
		error_and_exit_stg(stg, "Error\nInvalid string found.");
}

static	void	parse_line(t_scene *stg)
{
	char	**strs;
	char	*trimmed;
	char	letter;

	if (*stg->line == '\0')
		return ;
	if (stg->w && stg->h && stg->no && stg->ea && stg->we
		&& stg->so && stg->sprite && stg->floor && stg->ceil)
		parse_map(stg->line, stg);
	else
	{
		trimmed = ft_strtrim(stg->line, " \n\t\v\f\r");
		free(stg->line);
		stg->line = trimmed;
		if (stg->line[0] == 'C' || stg->line[0] == 'F')
		{
			letter = stg->line[0];
			stg->line = remove_spaces(&stg->line);
			ft_add_letter(' ', &stg->line, true);
			ft_add_letter(letter, &stg->line, true);
		}
		strs = ft_split(stg->line, ' ');
		verify_identifiers(strs, stg);
		ft_freearrays(strs);
	}
}

void	parse_stg(t_scene *stg, char *file)
{
	int	ret;
	int	fd;

	if (!validate_name(file))
		error_and_exit_stg(stg, "Error\nInvalid name. File must end with .cub.");
	ret = 1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_and_exit_stg(stg, "Error\nCould not open the file for reading.");
	while (ret > 0)
	{
		ret = get_next_line(fd, &stg->line);
		parse_line(stg);
		free(stg->line);
		stg->line = NULL;
	}
	validate_map(stg);
	close(fd);
}
