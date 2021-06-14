/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 19:48:12 by ngregori          #+#    #+#             */
/*   Updated: 2021/04/22 12:24:46 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_inner_circle(t_img *img, t_circle circle, int res_width)
{
	while (circle.radius > 0)
	{
		circle.radius--;
		draw_inner_circle(img, circle, res_width);
		draw_circle(img, circle, res_width);
	}
}

void	draw_line(t_img *img, t_line line, int res_width)
{
	int		i;
	int		x;
	int		y;
	double	dir_x;
	double	dir_y;

	dir_x = cos(line.dir);
	dir_y = sin(line.dir);
	i = -1;
	while (++i <= line.size)
	{
		x = dir_x * i + line.x;
		y = dir_y * i + line.y;
		img->addr[x + y * res_width] = line.color;
	}
}

void	draw_circle(t_img *img, t_circle circle, int res_width)
{
	int	x;
	int	y;

	while (circle.ang < 360)
	{
		x = circle.radius * cos(deg_to_rad(circle.ang)) + circle.x;
		y = circle.radius * sin(deg_to_rad(circle.ang)) + circle.y;
		img->addr[x + y * res_width] = circle.color;
		circle.ang++;
	}
}

void	draw_square(t_img *img, t_square square, int res_width)
{
	size_t	width;
	size_t	height;
	int		x;
	int		y;

	height = 0;
	while (height <= square.size)
	{
		width = 0;
		while (width <= square.size)
		{
			x = square.x + width;
			y = square.y + height;
			img->addr[x + y * res_width] = square.color;
			width++;
		}
		height++;
	}
}
