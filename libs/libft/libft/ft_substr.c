/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:32:54 by ngregori          #+#    #+#             */
/*   Updated: 2021/02/16 01:43:51 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	size;
	size_t	str_length;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str_length = ft_strlen(&s[start]);
	if (str_length < len)
		size = str_length;
	else
		size = len;
	sub_str = malloc(sizeof(char) * size + 1);
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, &s[start], size + 1);
	return (sub_str);
}
