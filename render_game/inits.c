/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:49:50 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/21 10:04:24 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_stg(t_scene *stg)
{
	stg->h = 0;
	stg->w = 0;
	stg->no = NULL;
	stg->so = NULL;
	stg->we = NULL;
	stg->ea = NULL;
	stg->sprite = NULL;
	stg->floor = NULL;
	stg->ceil = NULL;
	stg->tmp_map = NULL;
	stg->map = NULL;
	stg->map_width = 0;
	stg->map_size = 0;
	stg->line = NULL;
}

static	void	init_player(t_game *game)
{
	get_player_pos(game);
	game->player.circle.radius = game->mmt.size / 4.0;
	game->player.circle.color = 0x7F0000;
	game->player.circle.ang = 0;
	game->player.turn_dir = 0;
	game->player.walk_dir = 0;
	game->player.move_speed = 2;
	game->player.rot_speed = deg_to_rad(5);
	game->player.fov_ang = deg_to_rad(60);
	game->player.num_rays = game->stg.w;
	game->player.rays = malloc(sizeof (t_ray *) * game->player.num_rays);
	game->player.dtpp = (game->stg.w / 2) / tan(game->player.fov_ang / 2);
	game->player.ang_inc = game->player.fov_ang / game->player.num_rays;
	if (!game->player.rays)
		exit_game(game, "Error\nUnable to allocate memory for rays");
}

static	void	init_txts(t_game *game)
{
	game->txts.no.img = mlx_xpm_file_to_image(game->mlx, game->stg.no,
			&game->txts.no.width, &game->txts.no.height);
	game->txts.ea.img = mlx_xpm_file_to_image(game->mlx, game->stg.ea,
			&game->txts.ea.width, &game->txts.ea.height);
	game->txts.so.img = mlx_xpm_file_to_image(game->mlx, game->stg.so,
			&game->txts.so.width, &game->txts.so.height);
	game->txts.we.img = mlx_xpm_file_to_image(game->mlx, game->stg.we,
			&game->txts.we.width, &game->txts.we.height);
	game->txts.spr.img = mlx_xpm_file_to_image(game->mlx, game->stg.sprite,
			&game->txts.spr.width, &game->txts.spr.height);
	game->txts.no.addr = (int *)mlx_get_data_addr(game->txts.no.img,
			&game->txts.no.bpp, &game->txts.no.line_length, &game->txts.no.end);
	game->txts.ea.addr = (int *)mlx_get_data_addr(game->txts.ea.img,
			&game->txts.ea.bpp, &game->txts.ea.line_length, &game->txts.ea.end);
	game->txts.so.addr = (int *)mlx_get_data_addr(game->txts.so.img,
			&game->txts.so.bpp, &game->txts.so.line_length, &game->txts.so.end);
	game->txts.we.addr = (int *)mlx_get_data_addr(game->txts.we.img,
			&game->txts.we.bpp, &game->txts.we.line_length, &game->txts.we.end);
	game->txts.spr.addr = (int *)mlx_get_data_addr(game->txts.spr.img,
			&game->txts.spr.bpp, &game->txts.spr.line_length,
			&game->txts.spr.end);
}

void	init_wall_vars(t_ray *ray)
{
	ray->w_hrzt_hit = false;
	ray->w_hrzt_x = 0;
	ray->w_hrzt_y = 0;
	ray->w_vrtc_hit = false;
	ray->w_hrzt_x = 0;
	ray->w_hrzt_y = 0;
	ray->w_txt_pixel = 0;
}

void	init_stuff(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->stg.w, game->stg.h, "CUB3D");
	game->cube_size = 64;
	game->mmt.size = (game->stg.w / game->stg.map_width) / 3;
	game->sprs_num = 0;
	game->sprs = malloc(sizeof(t_sprite *));
	init_player(game);
	init_txts(game);
	create_rays(game);
	init_sprites(game);
}
