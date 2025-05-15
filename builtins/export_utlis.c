/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:07:26 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/15 21:14:56 by ababdoul         ###   ########.fr       */
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
	name = NULL;
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
		value = NULL;
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

// int	check_export_syntax(char **av, int i)
// {
// 	int	pos;

// 	if (!is_valid_varname_char(av[i][0], 1))
// 	{
// 		export_error(av[i]);
// 		return (FAILURE);
// 	}
// 	pos = 0;
// 	while (av[i][pos] != '\0' && av[i][pos] != '=' && av[i][pos] != '+')
// 	{
// 		if (!is_valid_varname_char(av[i][pos], 0))
// 			return (export_error(av[i]), FAILURE);
// 		pos++;
// 	}
// 	if (ft_strnstr(av[i], "+=", ft_strlen(av[i])))
// 	{
// 		pos = ft_strchr(av[i], '+') - av[i];
// 		if (pos > 0 && av[i][pos - 1] != '+' && av[i][pos + 1] == '=')
// 			return (SUCCESS);
// 		return (export_error(av[i]), FAILURE);
// 	}
// 	if (ft_strchr(av[i], '=') || av[i][pos] == '\0')
// 		return (SUCCESS);
// 	export_error(av[i]);
// 	return (FAILURE);
// }
