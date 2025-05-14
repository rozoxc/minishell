/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/14 18:17:32 by hfalati          ###   ########.fr       */
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

int process_export_arg(char *arg, t_obj *obj)
{
    char *name;
    char *value;
    char *existing_value;
	char *new_value;

    if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
        name = ft_substr(arg, 0, ft_strchr(arg, '+') - arg);
        value = ft_substr(arg, ft_strchr(arg, '+') - arg + 2, ft_strlen(arg));
        existing_value = lookup_env_value(obj, name);
        if (existing_value)
		{
			new_value = ft_strjoin(existing_value, value); // Append the value
            add_env(ft_strjoin(name, ft_strjoin("=", new_value)), &obj->env);
            free(new_value);
			new_value = NULL;
        }
		else
            add_env(ft_strjoin(name, ft_strjoin("=", value)), &obj->env); // Add as a new variable
        free(name);
        free(value);
		name = NULL;
		value = NULL;
    }
	else
	{
        int fond = check_fond(arg);
        if (fond == -1)
		{
            export_error(arg);
            return (FAILURE);
        }
		else if (fond != 0)
            add_env(arg, &obj->env);
    }
    return (SUCCESS);
}

int	is_valid_varname_char(char c, int is_first_char)
{
	if (is_first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

int	check_export_syntax(char **av, int i)
{
	int pos;

	if (!is_valid_varname_char(av[i][0], 1))
	{
		export_error(av[i]);
		return (FAILURE);
	}
	for (pos = 0; av[i][pos] != '\0' && av[i][pos] != '=' && av[i][pos] != '+'; pos++)
	{
		if (!is_valid_varname_char(av[i][pos], 0))
			return (export_error(av[i]), FAILURE);
	}
	if (ft_strnstr(av[i], "+=", ft_strlen(av[i])))
	{
		pos = ft_strchr(av[i], '+') - av[i];
		if (pos > 0 && av[i][pos - 1] != '+' && av[i][pos + 1] == '=')
			return (SUCCESS);
		return (export_error(av[i]),FAILURE);
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
