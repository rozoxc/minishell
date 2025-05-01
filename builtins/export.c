/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/30 17:49:37 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_envs(t_obj *obj)
{
	t_env	*current;
	int		i;
	char	*name;
	char	*value;

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
			
			// Find the equals sign position
			i = 0;
			while (current->value[i] && current->value[i] != '=')
				i++;
			
			// Print the variable name
			name = ft_substr(current->value, 0, i);
			ft_putstr_fd(name, STDOUT_FILENO);
			free(name);
			
			// If there's a value, print it with quotes
			if (current->value[i] == '=')
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				value = ft_substr(current->value, i + 1, ft_strlen(current->value) - i - 1);
				ft_putstr_fd(value, STDOUT_FILENO);
				free(value);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			
			ft_putstr_fd("\n", STDOUT_FILENO);
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
			fond = 2;
			if (fond == -1)
			{
				ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
				ft_putendl_fd(av[i], STDERR_FILENO);
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
