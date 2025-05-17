/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:04:02 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/17 14:17:57 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_obj *obj)
{
	t_env	*current;

	if (!obj)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (determine_exit_code(obj, 1), 1);
	}
	current = obj->env;
	while ((current != NULL && obj->cmd->argv[1] == NULL) || \
		(current != NULL && obj->cmd->argv[1][0] == '\0'))
	{
		if (current->value)
		{
			if (ft_strchr(current->value, '='))
				ft_putendl_fd(current->value, STDOUT_FILENO);
		}
		current = current->next;
	}
	return (determine_exit_code(obj, 0), SUCCESS);
}
