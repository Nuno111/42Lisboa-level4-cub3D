/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:45:27 by ngregori          #+#    #+#             */
/*   Updated: 2021/02/12 00:44:31 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;
	size_t	length;

	length = ft_strlen(s);
	newstr = malloc(sizeof(char) * length + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s, length + 1);
	return (newstr);
}
