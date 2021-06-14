/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:24:29 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 18:01:43 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	**realloc_sprs(t_game *game, t_sprite **arr, t_sprite *new)
{
	t_sprite	**new_arr;
	int			i;

	i = -1;
	new_arr = malloc(sizeof(t_sprite *) * (game->sprs_num + 1));
	if (!new_arr)
		exit_game(game, "Error\nFailed to allocate memory for sprites array.");
	while (++i < game->sprs_num)
		new_arr[i] = arr[i];
	new_arr[i] = new;
	while (++i < game->sprs_num)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
	return (new_arr);
}

double	get_spr_angle(t_game *game, double spr_x, double spr_y)
{
	double	x;
	double	y;
	double	player_x;
	double	player_y;
	double	ang;

	player_x = (game->player.circle.x / game->mmt.size) * game->cube_size;
	player_y = (game->player.circle.y / game->mmt.size) * game->cube_size;
	x = spr_x - player_x;
	y = spr_y - player_y;
	ang = normalize_angle(atan2(y, x) - game->player.rot_ang);
	return (ang);
}

bool	is_spr_visible(t_game *game, double ang)
{
	if (ang < -M_PI)
		ang += 2.0 * M_PI;
	if (ang > M_PI)
		ang -= 2.0 * M_PI;
	ang = fabs(ang);
	return (ang < game->player.fov_ang / 2);
}

double	get_spr_distance(t_game *game, double spr_x, double spr_y)
{
	double	player_x;
	double	player_y;

	player_x = (game->player.circle.x / game->mmt.size) * game->cube_size;
	player_y = (game->player.circle.y / game->mmt.size) * game->cube_size;
	return (get_dist(spr_x, spr_y, player_x, player_y));
}

void	get_spr_pos(t_game *game, int i)
{
	double	x_centre;
	double	y_centre;
	double	x_spr_centre;
	double	y_spr_centre;

	x_centre = game->stg.w / 2;
	x_spr_centre = tan(game->sprs[i]->ang) * game->player.dtpp;
	y_centre = game->stg.h / 2;
	y_spr_centre = game->sprs[i]->h / 2;
	game->sprs[i]->x_strt = x_centre + x_spr_centre - (game->sprs[i]->h / 2);
	game->sprs[i]->y_strt = y_centre - y_spr_centre;
	if (game->sprs[i]->y_strt < 0)
		game->sprs[i]->y_strt = 0;
}
