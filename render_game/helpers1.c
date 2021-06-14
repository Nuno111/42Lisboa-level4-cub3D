/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:29:00 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 18:46:11 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(double x, double y, t_game *game)
{
	size_t	index_w;
	size_t	index_h;
	char	c;

	index_w = x / game->mmt.size;
	index_h = y / game->mmt.size;
	if (index_w >= game->stg.map_width || index_h >= game->stg.map_size)
		return (false);
	c = game->stg.map[index_h][index_w];
	if (c == '1')
		return (true);
	return (false);
}

bool	is_sprite(double x, double y, t_game *game)
{
	size_t	index_w;
	size_t	index_h;
	char	c;

	index_w = x / game->mmt.size;
	index_h = y / game->mmt.size;
	if (index_w >= game->stg.map_width || index_h >= game->stg.map_size)
		return (false);
	c = game->stg.map[index_h][index_w];
	if (c == '2')
		return (true);
	return (false);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307 || keycode == ESC)
		exit_game(game, NULL);
	if (keycode == 119 || keycode == W)
		game->player.walk_dir = UP;
	else if (keycode == 100 || keycode == D)
		game->player.walk_dir = RIGHT;
	else if (keycode == 115 || keycode == S)
		game->player.walk_dir = DOWN;
	else if (keycode == 97 || keycode == A)
		game->player.walk_dir = LEFT;
	else if (keycode == 65361 || keycode == ARR_LEFT)
		game->player.turn_dir = -1;
	else if (keycode == 65363 || keycode == ARR_RIGHT)
		game->player.turn_dir = 1;
	return (1);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 100 || keycode == 115 || keycode == 97
		|| keycode == W || keycode == D || keycode == S || keycode == A)
		game->player.walk_dir = 0;
	else if (keycode == 65363 || keycode == 65361
		|| keycode == ARR_LEFT || keycode == ARR_RIGHT)
		game->player.turn_dir = 0;
	return (1);
}
