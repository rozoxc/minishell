/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/07 23:07:20 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Print all environment variables */
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
		print_env_var(current);
		current = current->next;
	}
	return (0);
}

/* Handle error messages for export command */
void	export_error(char *arg)
{
	ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
}

/* Process a single export argument */
int	process_export_arg(char *arg, t_obj *obj)
{
	int	fond;

	fond = check_fond(arg);
	if (fond == -1)
	{
		export_error(arg);
		return (FAILURE);
	}
	else if (fond != 0)
		add_env(arg, &obj->env);
	return (SUCCESS);
}

/* Check for invalid export syntax */
int	check_export_syntax(char **av, int i)
{
	if (!(ft_strchr(av[i], '=')) && av[i + 1] && av[i + 1][0] == '=')
	{
		export_error(av[i + 1]);
		return (FAILURE);
	}
	return (SUCCESS);
}

/* Main export function */
int	ft_export(char **av, t_obj *obj)
{
	int	i;

	i = 1;
	if (av[1])
	{
		while (av[i])
		{
			if (check_export_syntax(av, i) == FAILURE)
				return (FAILURE);
			if (process_export_arg(av[i], obj) == FAILURE)
				return (FAILURE);
			i++;
		}
	}
	else
	{
		if (print_envs(obj))
			return (FAILURE);
	}
	return (SUCCESS);
}
