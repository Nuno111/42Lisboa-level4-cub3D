/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_letter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:35:30 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/20 13:51:59 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_letter(char c, char **buffer, bool start)
{
	char	*new;

	new = malloc(sizeof(char) * 2);
	if (!new)
		return ;
	new[0] = c;
	new[1] = '\0';
	if (*buffer == NULL)
		*buffer = new;
	else if (!start)
		*buffer = str_join_free(buffer, &new);
	else
		*buffer = str_join_free(&new, buffer);
}
