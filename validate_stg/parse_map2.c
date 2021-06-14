/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:03:11 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 19:36:51 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	char_not_valid(int i, int j, char **m)
{
	char	*valid;

	valid = "1+ ";
	if (!ft_strchr(valid, m[i - 1][j - 1])
	|| !ft_strchr(valid, m[i - 1][j])
	|| !ft_strchr(valid, m[i - 1][j + 1])
	|| !ft_strchr(valid, m[i][j - 1])
	|| !ft_strchr(valid, m[i][j + 1])
	|| !ft_strchr(valid, m[i + 1][j - 1])
	|| !ft_strchr(valid, m[i + 1][j])
	|| !ft_strchr(valid, m[i + 1][j + 1])
	)
		return (true);
	return (false);
}

bool	plus_found(int i, int j, char **m)
{
	char	*charset;

	charset = "NESW02";
	if (ft_strchr(charset, m[i][j]))
	{
		if (m[i - 1][j - 1] == '+'
		|| m[i - 1][j] == '+'
		|| m[i - 1][j + 1] == '+'
		|| m[i][j - 1] == '+'
		|| m[i][j + 1] == '+'
		|| m[i + 1][j - 1] == '+'
		|| m[i + 1][j] == '+'
		|| m[i + 1][j + 1] == '+'
		)
			return (true);
	}
	return (false);
}
