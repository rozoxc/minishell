/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/27 22:02:48 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_envs(t_obj *obj)
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
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(current->value, STDOUT_FILENO);
		}
		current = current->next;
	}
	return (0);
}

int	ft_export(char **av, t_obj *obj)
{
	int	i;
	int	fond;

	i = 1;
	fond = 0;
	if (av[1])
	{
		while (av[i])
		{
			fond = check_fond(av[i]);
			if (fond == -1)
			{
				printf("export: not avalid in this context: %s\n", av[i]);
				return (FAILURE);
			}
			else if (fond != 0)
				add_env(av[i], &obj->env);
			i++;
		}
	}
	else
		if (print_envs(obj))
			return (FAILURE);
	return (SUCCESS);
}
