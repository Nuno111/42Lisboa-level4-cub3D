/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:58:16 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 20:03:25 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length1;
	size_t	length2;
	char	*arr;

	if (s1)
		length1 = ft_strlen(s1);
	else
		length1 = 0;
	if (s2)
		length2 = ft_strlen(s2);
	else
		length2 = 0;
	arr = malloc(sizeof(char) * (length1 + length2) + 1);
	if (!arr)
		return (NULL);
	ft_memmove(arr, s1, length1);
	ft_memmove(&arr[length1], s2, length2 + 1);
	return (arr);
}
