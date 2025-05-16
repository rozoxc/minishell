/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/16 18:46:00 by hfalati          ###   ########.fr       */
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

int	handle_append_export(char *arg, t_obj *obj)
{
	char	*name;
	char	*value;
	char	*existing_value;
	char	*new_value;

	name = ft_substr(arg, 0, ft_strchr(arg, '+') - arg);
	value = ft_substr(arg, ft_strchr(arg, '+') - arg + 2, ft_strlen(arg));
	existing_value = lookup_env_value(obj, name);
	if (existing_value)
	{
		new_value = ft_strjoin(existing_value, value);
		add_env(ft_strjoin(name, ft_strjoin("=", new_value)), &obj->env);
		free(new_value);
		new_value = NULL;
	}
	else
		add_env(ft_strjoin(name, ft_strjoin("=", value)), &obj->env);
	free(name);
	free(value);
	name = NULL;
	value = NULL;
	return (SUCCESS);
}

int	process_export_arg(char *arg, t_obj *obj)
{
	int	fond;

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (handle_append_export(arg, obj));
	fond = check_fond(arg);
	if (fond == -1)
	{
		printf("hey\n");
		export_error(arg);
		return (FAILURE);
	}
	else if (fond != 0)
		add_env(arg, &obj->env);
	return (SUCCESS);
}

int	check_export_syntax(char **av, int i)
{
	int	pos;

	if (!is_valid_varname_char(av[i][0], 1))
	{
		export_error(av[i]);
		return (FAILURE);
	}
	pos = 0;
	while (av[i][pos] != '\0' && av[i][pos] != '=' && av[i][pos] != '+')
	{
		if (!is_valid_varname_char(av[i][pos], 0))
			return (export_error(av[i]), FAILURE);
		pos++;
	}
	if (ft_strnstr(av[i], "+=", ft_strlen(av[i])))
	{
		pos = ft_strchr(av[i], '+') - av[i];
		if (pos > 0 && av[i][pos - 1] != '+' && av[i][pos + 1] == '=')
			return (SUCCESS);
		return (export_error(av[i]), FAILURE);
	}
	if (ft_strchr(av[i], '=') || av[i][pos] == '\0')
		return (SUCCESS);
	export_error(av[i]);
	return (FAILURE);
}

int	ft_export(char **av, t_obj *obj)
{
	int	i;

	i = 1;
	if (av[1] && av[1][0] != '\0')
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
	else if ((av[0] != NULL) && (av[1] == NULL || av[1][0] == '\0'))
	{
		if (print_envs(obj))
			return (FAILURE);
	}
	return (SUCCESS);
}
