/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utlis_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:58:30 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/09 12:22:30 by hfalati          ###   ########.fr       */
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

char	*lookup_env_value(t_obj *obj, char *str)
{
	t_env	*env;
	int		equal;
	char	*value;

	env = obj->env;
	value = NULL;
	while (env && value == NULL)
	{
		equal = check_equal(env->value);
		if ((ft_strncmp(str, env->value, ft_strlen(str)) == 0
				&& ft_strncmp(env->value, str, equal) == 0))
			value = ft_strdup(ft_strchr(env->value, '=') + 1);
		env = env->next;
	}
	return (value);
}
