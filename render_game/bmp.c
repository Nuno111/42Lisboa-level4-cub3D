/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:17:40 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/20 11:09:21 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	write_image_data(t_game *game, int fd)
{
	int	i;
	int	j;

	i = game->stg.h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < game->stg.w)
		{
			write(fd, &game->img.addr[i * game->stg.w + j], 4);
			j++;
		}
		i--;
	}
}

static	void	write_header_data(t_game *game, int fd)
{
	write(fd, &game->bpm_header.bf_type, 2);
	write(fd, &game->bpm_header.bf_size, 4);
	write(fd, &game->bpm_header.bf_reserved1, 2);
	write(fd, &game->bpm_header.bf_reserved2, 2);
	write(fd, &game->bpm_header.bf_offbits, 4);
	write(fd, &game->bpm_info_header.bi_size, 4);
	write(fd, &game->bpm_info_header.bi_width, 4);
	write(fd, &game->bpm_info_header.bi_height, 4);
	write(fd, &game->bpm_info_header.bi_planes, 2);
	write(fd, &game->bpm_info_header.bi_bitcount, 2);
	write(fd, &game->bpm_info_header.bi_compression, 4);
	write(fd, &game->bpm_info_header.bi_sizeimage, 4);
	write(fd, &game->bpm_info_header.bi_xpelspermeter, 4);
	write(fd, &game->bpm_info_header.bi_ypelspermeter, 4);
	write(fd, &game->bpm_info_header.bi_clrused, 4);
	write(fd, &game->bpm_info_header.bi_clrimportant, 4);
}

static	void	define_header_data(t_game *game)
{
	game->bpm_header.bf_type[0] = 'B';
	game->bpm_header.bf_type[1] = 'M';
	game->bpm_header.bf_size = game->stg.h * game->stg.w + 54;
	game->bpm_header.bf_reserved1 = 0;
	game->bpm_header.bf_reserved2 = 0;
	game->bpm_header.bf_offbits = 54;
	game->bpm_info_header.bi_size = 40;
	game->bpm_info_header.bi_width = game->stg.w;
	game->bpm_info_header.bi_height = game->stg.h;
	game->bpm_info_header.bi_planes = 1;
	game->bpm_info_header.bi_bitcount = game->img.bpp;
	game->bpm_info_header.bi_compression = 0;
	game->bpm_info_header.bi_sizeimage = 0;
	game->bpm_info_header.bi_xpelspermeter = 2835;
	game->bpm_info_header.bi_ypelspermeter = 2835;
	game->bpm_info_header.bi_clrused = 0;
	game->bpm_info_header.bi_clrimportant = 0;
}

void	save_and_exit(t_game *game)
{
	int				fd;

	fd = open("rendered_image.bmp", O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		exit_game(game, "Error\nCouldn't open a bmp file for writing.");
	define_header_data(game);
	write_header_data(game, fd);
	write_image_data(game, fd);
	close(fd);
	exit_game(game, NULL);
}
