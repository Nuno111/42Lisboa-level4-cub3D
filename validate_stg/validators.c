/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 23:22:37 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/20 16:59:15 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_r(t_scene *stg, char **strs)
{
	if (!strs[1] || !strs[2] || strs[3] || stg->w)
		error_and_exit_stg(stg, "Error\nProblem when handling resolution.");
	if (ft_str_is_numeric(strs[1]) && ft_str_is_numeric(strs[2]))
	{
		stg->w = ft_atoi(strs[1]);
		stg->h = ft_atoi(strs[2]);
		if (stg->w <= 0 || stg->h <= 0)
			error_and_exit_stg(stg, "Error\nInvalid input for resolution.");
		if (stg->w > 2560)
			stg->w = 2560;
		if (stg->h > 1440)
			stg->h = 1400;
	}
	else
		error_and_exit_stg(stg, "Error\nInvalid string format");
}

void	validate_floor_ceil(t_scene *stg, t_color **floor_or_ceil, char **strs)
{
	char	**tmp_strs;

	if (*floor_or_ceil || !validate_string(strs[1]) || strs[2])
		error_and_exit_stg(stg, "Error\nString is not properly formatted.");
	tmp_strs = ft_split(strs[1], ',');
	if (!tmp_strs[0] || !tmp_strs[1] || !tmp_strs[2])
		error_and_exit_stg(stg, "Error\n3 color values are needed.");
	validate_floor_ceil2(stg, floor_or_ceil, tmp_strs);
	ft_freearrays(tmp_strs);
}

void	validate_textures(t_scene *stg, char **path, char **strs)
{
	char	*tmp;
	size_t	len;
	int		validate_file;
	char	*tr;

	if (!strs[1] || *path)
		error_and_exit_stg(stg, "Error\nProblem found when handling path.");
	tmp = ft_strdup(strs[1]);
	if (!tmp)
		error_and_exit_stg(stg, "Error\nProblem found when handling path.");
	*path = tmp;
	tr = ft_strtrim(*path, " \n\t\v\f\r");
	len = ft_strlen(tr);
	if ((tr[len - 1] != 'm' || tr[len - 2] != 'p' || tr[len - 3] != 'x'
			|| tmp[len - 4] != '.') && (tr[len - 1] != 'g' || tr[len - 2] != 'n'
			|| tr[len - 3] != 'p' || tr[len - 4] != '.'))
	{
		free(tr);
		error_and_exit_stg(stg, "Error\nProblem found when handling path.");
	}
	validate_file = open(tr, O_RDONLY);
	free(tr);
	if (validate_file == -1)
		error_and_exit_stg(stg, "Error\nCould not open file for reading");
	close(validate_file);
}

bool	validate_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len <= 4)
		return (false);
	if (file[len - 1] == 'b' && file[len - 2] == 'u'
		&& file[len - 3] == 'c' && file[len - 4] == '.')
		return (true);
	return (false);
}

void	validate_map(t_scene *stg)
{
	stg->map = linked_to_array(stg, stg->tmp_map);
	verify_position(stg);
	create_fake_map(stg);
	verify_walls(stg, stg->map);
}
