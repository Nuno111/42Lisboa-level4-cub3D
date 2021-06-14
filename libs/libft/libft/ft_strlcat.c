/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:17:41 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 20:06:47 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	length = 0;
	while (dst[length] && length < size)
		length += 1;
	i = length;
	while (src[length - i] && length + 1 < size)
	{
		dst[length] = src[length - i];
		length += 1;
	}
	if (i < size)
		dst[length] = '\0';
	return (i + ft_strlen(src));
}
