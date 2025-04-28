/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:04:02 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/27 22:03:11 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_obj *obj)
{
	t_env	*current;

	if (!obj)
	{
		ft_putstr_fd("minishell: env: invalid shell object\n", STDERR_FILENO);
		return (1);
	}
	current = obj->env;
	while (current != NULL)
	{
		if (current->value)
		{
			if (ft_strchr(current->value, '='))
				ft_putendl_fd(current->value, STDOUT_FILENO);
		}
		current = current->next;
	}
	return (0);
}
