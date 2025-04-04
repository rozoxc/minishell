/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:06:29 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/05 17:07:01 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*c;
	t_list	*n;

	if (!lst || !del)
		return ;
	c = *lst;
	while (c)
	{
		n = c->next;
		ft_lstdelone(c, del);
		c = n;
	}
	*lst = NULL;
}
