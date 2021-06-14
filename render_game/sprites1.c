/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:02:21 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 16:09:06 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprs(t_game *game)
{
	int			i;
	bool		sorted;
	t_sprite	*tmp;

	sorted = false;
	while (!sorted)
	{
		i = -1;
		sorted = true;
		while (++i < game->sprs_num - 1)
		{
			if (game->sprs[i]->dist < game->sprs[i + 1]->dist)
			{
				tmp = game->sprs[i];
				game->sprs[i] = game->sprs[i + 1];
				game->sprs[i + 1] = tmp;
				sorted = false;
			}
		}
	}
}

void	update_sprs(t_game *game)
{
	int			i;
	t_sprite	*spr;

	i = -1;
	while (++i < game->sprs_num)
	{
		spr = game->sprs[i];
		spr->dist = get_spr_distance(game, spr->x, spr->y);
		spr->ang = get_spr_angle(game, spr->x, spr->y);
		spr->visible = is_spr_visible(game, spr->ang);
		spr->h = (game->cube_size / spr->dist) * game->player.dtpp;
		get_spr_pos(game, i);
	}
	sort_sprs(game);
}

void	draw_sprt_strip(t_game *game, t_sprite *spr, int x_tex, int x_pox)
{
	int		y;
	int		y_tex;
	double	step;
	double	tex_pox;
	int		color;

	step = spr->txt.height / spr->h;
	tex_pox = (spr->y_strt - game->stg.h / 2 + spr->h / 2) * step;
	y = -1;
	while (++y < spr->h && y < game->stg.h)
	{
		y_tex = (int)tex_pox & (spr->txt.height - 1);
		tex_pox += step;
		color = spr->txt.addr[x_tex + y_tex * spr->txt.height];
		if (color < 0)
			continue ;
		game->img.addr[x_pox + (spr->y_strt + y) * game->stg.w] = color;
	}
}

void	draw_sprt(t_game *game, t_sprite *spr)
{
	double	width;
	int		i;
	int		j;
	int		x_pox;

	i = -1;
	width = spr->h / spr->txt.height;
	while (++i < spr->txt.width - 1)
	{
		j = -1;
		while (++j < width)
		{
			x_pox = (int)(spr->x_strt + i * width + j);
			if (x_pox >= 0 && x_pox <= game->stg.w - 1
				&& spr->dist < (game->player.rays[x_pox]->line.size
					/ game->mmt.size) * game->cube_size)
				draw_sprt_strip(game, spr, i, x_pox);
		}
	}
}

void	draw_sprites(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->sprs_num)
	{
		if (game->sprs[i]->visible)
			draw_sprt(game, game->sprs[i]);
	}
}
