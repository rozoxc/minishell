/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:20:13 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/16 01:23:44 by ababdoul         ###   ########.fr       */
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
		print_env_var(current);
		current = current->next;
	}
	return (0);
}

void	export_error(char *arg)
{
	ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
}

int	is_valid_varname_char(char c, int is_first_char)
{
	if (is_first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}
