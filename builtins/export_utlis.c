/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:07:26 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/16 15:07:48 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env_name(char *env_value)
{
	int		i;
	char	*name;

	i = 0;
	while (env_value[i] && env_value[i] != '=')
		i++;
	name = ft_substr(env_value, 0, i);
	ft_putstr_fd(name, STDOUT_FILENO);
	free(name);
}

/* Extract and print variable value */
void	print_env_value(char *env_value, int i)
{
	char	*value;

	if (env_value[i] == '=')
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		value = ft_substr(env_value, i + 1, ft_strlen(env_value) - i - 1);
		ft_putstr_fd(value, STDOUT_FILENO);
		free(value);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/* Print single environment variable */
void	print_env_var(t_env *current)
{
	int		i;

	if (current->value)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		i = 0;
		while (current->value[i] && current->value[i] != '=')
			i++;
		print_env_name(current->value);
		print_env_value(current->value, i);
	}
}
