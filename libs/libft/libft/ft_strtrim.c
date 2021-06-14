/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:18:12 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 19:59:33 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end_length;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	end_length = ft_strlen(s1);
	while (*s1 && ft_strrchr(set, *(s1 + end_length)))
		end_length--;
	if (end_length > 0)
		end_length++;
	return (ft_substr(s1, 0, end_length));
}
