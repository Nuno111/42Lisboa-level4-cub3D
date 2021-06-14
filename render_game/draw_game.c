/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 16:57:08 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceil(t_game *game, t_color color, bool floor)
{
	int	x;
	int	y;
	int	max;

	if (floor)
	{
		max = game->stg.h / 2;
		y = -1;
	}
	else
	{
		max = game->stg.h;
		y = game->stg.h / 2 - 1;
	}
	color.trgb = create_trgb(0, color.r, color.g, color.b);
	while (++y < max)
	{
		x = -1;
		while (++x < game->stg.w)
			game->img.addr[x + y * game->stg.w] = color.trgb;
	}
}

static	void	draw_wall_line(t_game *game, t_wall wall, int i)
{
	int		y;
	int		y_tex;
	int		x_tex;
	double	step;
	double	tex_pox;

	step = wall.tex.height / wall.height;
	tex_pox = (wall.y - game->stg.h / 2 + wall.height / 2) * step;
	x_tex = fmod((game->player.rays[i]->w_txt_pixel / game->mmt.size)
			* game->cube_size, wall.tex.width - 1);
	y = -1;
	while (++y < wall.height && y < game->stg.h)
	{
		y_tex = (int)tex_pox & (wall.tex.height - 1);
		game->img.addr[wall.x + (wall.y + y) * game->stg.w]
			= wall.tex.addr[y_tex * wall.tex.height + x_tex];
		tex_pox += step;
	}
}

void	draw_walls(t_game *game)
{
	int		i;
	t_wall	wall;

	i = 0;
	while (i < game->player.num_rays)
	{
		wall.height = get_wall_height(game, game->player.rays[i]);
		wall.x = i;
		wall.y = (game->stg.h / 2) - (wall.height / 2);
		if (wall.y < 0)
			wall.y = 0;
		wall.tex = assign_wall_texture(game, *game->player.rays[i]);
		draw_wall_line(game, wall, i);
		i++;
	}
}

void	draw_minimap(t_scene *stg, t_game *game)
{
	int	width;
	int	height;

	height = 1;
	while (stg->map[height + 1])
	{
		width = 1;
		while (stg->map[height][width + 1])
		{
			if (stg->map[height][width] == '1')
				game->mmt.color = 0x293250;
			else if (stg->map[height][width] == '0'
				|| ft_strchr("NESW", stg->map[height][width]))
				game->mmt.color = 0xFFD55A;
			else
				game->mmt.color = 0x001FFF;
			game->mmt.x = width * game->mmt.size;
			game->mmt.y = height * game->mmt.size;
			draw_square(&game->img, game->mmt, game->stg.w);
			width++;
		}
		height++;
	}
}

void	draw_rays(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->player.num_rays)
		draw_line(&game->img, game->player.rays[i]->line, game->stg.w);
}
