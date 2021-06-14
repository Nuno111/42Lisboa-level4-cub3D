/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:39:24 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 17:56:06 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_dist(double x, double y, double hit_x, double hit_y)
{
	double	distance;

	distance = (hit_x - x) * (hit_x - x) + (hit_y - y) * (hit_y - y);
	return (sqrt(distance));
}

double	normalize_angle(double ray_ang)
{
	ray_ang = fmod(ray_ang, 2 * M_PI);
	if (ray_ang < 0)
		ray_ang += (2 * M_PI);
	return (ray_ang);
}

void	did_ray_hit_wall(t_game *game, t_ray *ray, t_intercect itc, bool hrzt)
{
	while (itc.x < game->stg.w && itc.y < game->stg.h
		&& itc.x > 0 && itc.y > 0)
	{
		if (is_wall(itc.x, itc.y, game))
		{
			if (hrzt)
			{
				ray->w_hrzt_hit = true;
				ray->w_hrzt_x = itc.x;
				ray->w_hrzt_y = itc.y;
			}
			else
			{
				ray->w_vrtc_hit = true;
				ray->w_vrtc_x = itc.x;
				ray->w_vrtc_y = itc.y;
			}
			return ;
		}
		else
		{
			itc.x += itc.x_step;
			itc.y += itc.y_step;
		}
	}
}

void	get_horizontal_intercection(t_game *game, t_ray *ray)
{
	t_intercect	intercect;

	intercect.x_offset = 0;
	intercect.y = floor(ray->line.y / game->mmt.size) * game->mmt.size;
	if (!ray->facing_up)
		intercect.y += game->mmt.size;
	intercect.x = ray->line.x + (intercect.y - ray->line.y)
		/ tan(ray->line.dir);
	intercect.y_step = game->mmt.size;
	if (ray->facing_up)
		intercect.y_step *= -1;
	intercect.x_step = game->mmt.size / tan(ray->line.dir);
	if (!ray->facing_right && intercect.x_step > 0)
		intercect.x_step *= -1;
	if (ray->facing_right && intercect.x_step < 0)
		intercect.x_step *= -1;
	if (ray->facing_up)
		intercect.y -= 0.00001;
	else
		intercect.y_offset = 0;
	did_ray_hit_wall(game, ray, intercect, true);
}

void	get_vertical_intercection(t_game *game, t_ray *ray)
{
	t_intercect	intercect;

	intercect.y_offset = 0;
	intercect.x = floor(ray->line.x / game->mmt.size) * game->mmt.size;
	if (ray->facing_right)
		intercect.x += game->mmt.size;
	intercect.y = ray->line.y + (intercect.x - ray->line.x)
		* tan(ray->line.dir);
	intercect.x_step = game->mmt.size;
	if (!ray->facing_right)
		intercect.x_step *= -1;
	intercect.y_step = game->mmt.size * tan(ray->line.dir);
	if (ray->facing_up && intercect.y_step > 0)
		intercect.y_step *= -1;
	if (!ray->facing_up && intercect.y_step < 0)
		intercect.y_step *= -1;
	if (!ray->facing_right)
		intercect.x -= 0.00001;
	did_ray_hit_wall(game, ray, intercect, false);
}
