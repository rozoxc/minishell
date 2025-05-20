/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:07:26 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/20 12:34:24 by hfalati          ###   ########.fr       */
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

void	export_error(char *arg, t_obj *obj)
{
	ft_putstr_fd("export: not a valid identifier: ", 2);
	ft_putendl_fd(arg, 2);
	determine_exit_code(obj, 1);
}

int	is_valid_varname_char(char c, int is_first_char)
{
	if (is_first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}
