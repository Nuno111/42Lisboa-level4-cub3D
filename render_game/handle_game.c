/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:34:11 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 16:37:07 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	draw_game(t_game *game)
{
	draw_floor_ceil(game, *game->stg.floor, true);
	draw_floor_ceil(game, *game->stg.ceil, false);
	draw_walls(game);
	draw_sprites(game);
	draw_minimap(&game->stg, game);
	draw_circle(&game->img, game->player.circle, game->stg.w);
	draw_inner_circle(&game->img, game->player.circle, game->stg.w);
	draw_rays(game);
}

static	int	render_next_frame(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, game->stg.w, game->stg.h);
	game->img.addr = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.end);
	update_player(game);
	reset_rays(game);
	update_rays(game);
	update_sprs(game);
	draw_game(game);
	if (game->screenshot)
		save_and_exit(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = NULL;
	game->img.addr = NULL;
	return (1);
}

void	render_game(t_game *game)
{
	init_stuff(game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, handle_destroy, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_loop(game->mlx);
}
