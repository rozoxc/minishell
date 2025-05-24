/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/24 22:55:09 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	swap_strings(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	sort_by_first_char(char **arr, t_obj *obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < obj->count_env)
	{
		j = 0;
		while (j < obj->count_env - i)
		{
			if (arr[j][0] > arr[j + 1][0])
				swap_strings(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

int	print_envs(t_obj *obj)
{
	int i = 0;
	char **env;

	env = env_to_array(obj->env);
	sort_by_first_char(env, obj);
	if (!obj)
	{
		ft_putstr_fd("minishell: env: invalid shell object\n", STDERR_FILENO);
		return (determine_exit_code(obj, 1), 1);
	}
	while (env[i] != NULL)
	{
		print_env_var(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	return (determine_exit_code(obj, 0), 0);
}

int	handle_append_export(char *arg, t_obj *obj, char *full_var)
{
	char	*name;
	char	*value;
	char	*existing_value;
	char	*temp1;
	char	*temp2;

	name = ft_substr(arg, 0, ft_strchr(arg, '+') - arg);
	value = ft_substr(arg, ft_strchr(arg, '+') - arg + 2, ft_strlen(arg));
	existing_value = lookup_env_value(obj, name);
	if (existing_value)
		temp1 = ft_strjoin(existing_value, value);
	else
		temp1 = ft_strdup(value);
	temp2 = ft_strjoin("=", temp1);
	full_var = ft_strjoin(name, temp2);
	add_env(full_var, &obj->env);
	free(name);
	free(value);
	free(temp1);
	free(temp2);
	free(full_var);
	free(existing_value);
	return (determine_exit_code(obj, 0), SUCCESS);
}

int	process_export_arg(char *arg, t_obj *obj)
{
	int		fond;
	char	*full_var;

	full_var = NULL;
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (handle_append_export(arg, obj, full_var));
	fond = check_fond(arg);
	if (fond == -1)
	{
		export_error(arg, obj);
		return (FAILURE);
	}
	else if (fond != 0)
		add_env(arg, &obj->env);
	return (determine_exit_code(obj, 0), SUCCESS);
}

int	ft_export(char **av, t_obj *obj)
{
	int	count;

	count = 0;
	if ((av[0] != NULL) && (av[1] && av[1][0] != '\0'))
		handle_export_args(av, obj, &count);
	else if ((av[0] != NULL) && (av[1] == NULL || av[1][0] == '\0'))
		if (print_envs(obj))
			return (determine_exit_code(obj, 1), FAILURE);
	if (count >= 1)
		return (determine_exit_code(obj, 1), FAILURE);
	return (determine_exit_code(obj, 0), SUCCESS);
}
