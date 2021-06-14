/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:06:47 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/14 13:56:40 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return (trgb & (0xff << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xff << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xff << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xff);
}
