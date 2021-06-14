/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:00:07 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 20:10:12 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_list(t_list **lst)
{
	t_list	*tmp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			tmp = NULL;
		}
		lst = NULL;
	}
}
