/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:31:59 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 17:47:23 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_game *game, int x, int y)
{
	t_sprite	*spr;

	spr = malloc(sizeof(t_sprite));
	if (!spr)
		exit_game(game, "Error\nFailed to allocate memory for sprite.");
	spr->txt = game->txts.spr;
	spr->x = game->cube_size * (x + 0.5);
	spr->y = game->cube_size * (y + 0.5);
	if (game->sprs_num == 0)
		game->sprs[game->sprs_num] = spr;
	else
		game->sprs = realloc_sprs(game, game->sprs, spr);
	game->sprs_num++;
}

void	init_sprites(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->stg.map[y])
	{
		x = 0;
		while (game->stg.map[y][x])
		{
			if (game->stg.map[y][x] == '2')
				init_sprite(game, x, y);
			x++;
		}
		y++;
	}
}
