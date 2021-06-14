/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:21:15 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 20:18:02 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_is_numeric(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}
