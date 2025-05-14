/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utlis_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:58:30 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/14 11:12:58 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_special_chars(t_obj *obj, char *str)
{
	if (*str == '\0')
		return (ft_strdup("$"));
	else if (*str == '%')
		return (ft_strdup("$%"));
	else if (*str == '+')
		return (ft_strdup("$+"));
	else if (*str == '?')
		return (ft_strjoin2(NULL, ft_itoa(obj->exit_code), 3));
	else if (*str == '.')
		return (ft_strdup("$."));
	else if (*str == ',')
		return (ft_strdup("$,"));
	else if (*str == '/')
		return (ft_strdup("$/"));
	return (NULL);
}

char	*find_env_value(t_env *env, char *var_name)
{
	char	*value;
	int		equal;

	value = NULL;
	while (env && value == NULL)
	{
		equal = check_equal(env->value);
		if ((ft_strncmp(var_name, env->value, ft_strlen(var_name)) == 0
				&& ft_strncmp(env->value, var_name, equal) == 0))
		{
			if (ft_strchr(env->value, '='))
				value = ft_strdup(ft_strchr(env->value, '=') + 1);
		}
		env = env->next;
	}
	return (value);
}

char	*get_env_variable(t_obj *obj, char *str, char **suffix_ptr)
{
	t_env	*env;
	int		var_len;
	char	*var_name;
	char	*value;
	char	*suffix;

	env = obj->env;
	var_len = 0;
	while (str[var_len] && (ft_isalnum(str[var_len]) || str[var_len] == '_'))
		var_len++;
	if (var_len == 0)
		return (NULL);
	var_name = ft_substr(str, 0, var_len);
	if (!var_name)
		return (NULL);
	suffix = ft_strdup(str + var_len);
	if (!suffix)
	{
		free(var_name);
		return (NULL);
	}
	*suffix_ptr = suffix;
	value = find_env_value(env, var_name);
	free(var_name);
	return (value);
}

char	*lookup_env_value(t_obj *obj, char *str)
{
	char	*value;
	char	*suffix;
	char	*result;

	value = get_env_variable(obj, str, &suffix);
	if (!value)
	{
		free(suffix);
		return (NULL);
	}
	if (suffix[0] != '\0')
	{
		result = ft_strjoin(value, suffix);
		free(value);
		value = result;
	}
	free(suffix);
	return (value);
}
