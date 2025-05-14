/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/14 16:44:49 by ababdoul         ###   ########.fr       */
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

/* Process a single export argument */
int process_export_arg(char *arg, t_obj *obj)
{
    char *name;
    char *value;
    char *existing_value;
	char *new_value;

    // Check if the argument contains "+="
    if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
        name = ft_substr(arg, 0, ft_strchr(arg, '+') - arg); // Extract variable name
        value = ft_substr(arg, ft_strchr(arg, '+') - arg + 2, ft_strlen(arg)); // Extract value to append

        // Check if the variable already exists
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

int	check_export_syntax(char **av, int i)
{
	int pos;

	if (!(ft_strchr(av[i], '=')) && av[i + 1] && av[i + 1][0] == '=')
	{
		printf("first\n");
		export_error(av[i + 1]);
		return (FAILURE);
	}
	pos = ft_strchr(av[i], '+') - av[i];
	if (pos == 0 || pos == (int)ft_strlen(av[i]) - 1)
	{
		printf("seconde\n");
		export_error(av[i]);
		return (FAILURE);
	}
	if (ft_strnstr(av[i], "+=", ft_strlen(av[i])))
	{
		pos = ft_strchr(av[i], '+') - av[i];
		printf("position -- > :%d\n", pos);
		if (pos > 0 && av[i][pos - 1] == '+')
		{
			printf("third\n");
			export_error(av[i]);
			return (FAILURE);
		}
		if (pos == 0 || av[i][pos - 1] == '+')
		{
			export_error(av[i]);
			return (FAILURE);
		}
	}
	else if (av[i][0] == '$' && av[i][1] == '\0')
	{
		printf("finale\n");
		export_error(av[i]);
		return (FAILURE);
	}
	return (SUCCESS);
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
