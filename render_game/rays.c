/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:21:00 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 16:11:28 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_rays(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->player.num_rays)
	{
		game->player.rays[i]->facing_right = false;
		game->player.rays[i]->facing_up = false;
		game->player.rays[i]->line.dir = 0;
		game->player.rays[i]->line.size = 0;
		game->player.rays[i]->line.x = 0;
		game->player.rays[i]->line.y = 0;
		game->player.rays[i]->w_hrzt_hit = false;
		game->player.rays[i]->w_hrzt_x = 0;
		game->player.rays[i]->w_hrzt_y = 0;
		game->player.rays[i]->w_vrtc_hit = false;
		game->player.rays[i]->w_vrtc_x = 0;
		game->player.rays[i]->w_vrtc_y = 0;
		game->player.rays[i]->w_txt_pixel = 0;
	}
}

t_ray	*create_ray(t_game *game, double ray_ang)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit_game(game, "Error\nUnable to allocate memory for ray.");
	ray->line.x = game->player.circle.x;
	ray->line.y = game->player.circle.y;
	ray->line.dir = normalize_angle(ray_ang);
	ray->line.color = game->player.circle.color;
	if (ray->line.dir > M_PI && ray->line.dir < 2 * M_PI)
		ray->facing_up = true;
	else
		ray->facing_up = false;
	if (ray->line.dir < 0.5 * M_PI || ray->line.dir > 1.5 * M_PI)
		ray->facing_right = true;
	else
		ray->facing_right = false;
	init_wall_vars(ray);
	return (ray);
}

void	update_rays(t_game *game)
{
	int		i;
	double	ray_ang;

	i = -1;
	ray_ang = game->player.rot_ang - (game->player.fov_ang / 2);
	while (++i < game->player.num_rays)
	{
		game->player.rays[i]->line.x = game->player.circle.x;
		game->player.rays[i]->line.y = game->player.circle.y;
		game->player.rays[i]->line.dir = normalize_angle(ray_ang);
		if (game->player.rays[i]->line.dir > M_PI
			&& game->player.rays[i]->line.dir < 2 * M_PI)
			game->player.rays[i]->facing_up = true;
		else
			game->player.rays[i]->facing_up = false;
		if (game->player.rays[i]->line.dir < 0.5 * M_PI
			|| game->player.rays[i]->line.dir > 1.5 * M_PI)
			game->player.rays[i]->facing_right = true;
		else
			game->player.rays[i]->facing_right = false;
		calc_wall_dist(game, game->player.rays[i]);
		ray_ang += game->player.ang_inc;
	}
}

void	create_rays(t_game *game)
{
	double	ray_ang;
	int		i;

	i = -1;
	ray_ang = game->player.rot_ang - (game->player.fov_ang / 2);
	while (++i < game->player.num_rays)
	{
		game->player.rays[i] = create_ray(game, ray_ang);
		calc_wall_dist(game, game->player.rays[i]);
		ray_ang += game->player.ang_inc;
	}
}
