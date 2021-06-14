/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 11:11:50 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 18:46:14 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_and_exit_stg(t_scene *stg, char *err_msg)
{
	free_stg(stg);
	printf("%s\n", err_msg);
	exit(SUCCESS);
}

void	free_sprites(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->sprs_num)
		free(game->sprs[i]);
	if (game->sprs)
		free(game->sprs);
}

void	exit_game(t_game *game, char *err_msg)
{
	free_stg(&game->stg);
	free_sprites(game);
	if (err_msg)
	{
		printf("%s\n", err_msg);
		exit(ERR);
	}
	exit(SUCCESS);
}

int	handle_destroy(t_game *game)
{
	exit_game(game, NULL);
	return (1);
}
