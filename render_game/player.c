/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:30:45 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/20 16:53:22 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	get_player_rotation(char c, t_game *game)
{
	if (c == 'N')
		game->player.rot_ang = -(M_PI / 2);
	else if (c == 'E')
		game->player.rot_ang = 0;
	else if (c == 'S')
		game->player.rot_ang = M_PI / 2;
	else if (c == 'W')
		game->player.rot_ang = M_PI;
}

void	get_player_pos(t_game *game)
{
	int	h;
	int	w;

	h = 0;
	while (game->stg.map[h])
	{
		w = 0;
		while (game->stg.map[h][w])
		{
			if (ft_strchr("NESW", game->stg.map[h][w]))
			{
				game->player.circle.x = (w * game->mmt.size);
				game->player.circle.y = (h * game->mmt.size);
				get_player_rotation(game->stg.map[h][w], game);
				return ;
			}
			w++;
		}
		h++;
	}
}

static	void	update_player_pos(t_game *game)
{
	double	ang;
	double	step;
	double	tmp_x;
	double	tmp_y;

	ang = game->player.rot_ang;
	if (game->player.walk_dir == 0)
		return ;
	if (game->player.walk_dir == UP)
		ang = normalize_angle(ang);
	else if (game->player.walk_dir == RIGHT)
		ang = normalize_angle(ang + M_PI / 2);
	else if (game->player.walk_dir == DOWN)
		ang = normalize_angle(ang + M_PI);
	else if (game->player.walk_dir == LEFT)
		ang = normalize_angle(ang - M_PI / 2);
	step = game->player.move_speed;
	tmp_x = game->player.circle.x + cos(ang) * step;
	tmp_y = game->player.circle.y + sin(ang) * step;
	if (!is_wall(tmp_x, tmp_y, game) && !is_sprite(tmp_x, tmp_y, game))
	{
		game->player.circle.x = tmp_x;
		game->player.circle.y = tmp_y;
	}
}

static	void	update_player_ang(t_game *game)
{
	if (game->player.turn_dir == 0)
		return ;
	game->player.rot_ang = normalize_angle(game->player.rot_ang
			+ game->player.turn_dir * game->player.rot_speed);
}

void	update_player(t_game *game)
{
	update_player_ang(game);
	update_player_pos(game);
}
