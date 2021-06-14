/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:32:21 by ngregori          #+#    #+#             */
/*   Updated: 2021/03/23 18:32:26 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_join_free(char **beg, char **end)
{
	char	*tmp;

	tmp = ft_strjoin(*beg, *end);
	free(*beg);
	free(*end);
	return (tmp);
}
