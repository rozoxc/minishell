/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:22:24 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/06 13:58:19 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_fond(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	if (str[0] == '=')
		return (-1);
	if (str[0] == '+')
		return (-1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			count++;
		if (count > 1)
			return (-1);
		if (str[i] == ' ' || str[i] == '?')
			return (-1);
		i++;
	}
	if (str[i] == '\0')
		return (i);
	return (i);
}

void	add_env(char *str, t_env **env)
{
	t_env	*tmp_env;
	int		fond;

	tmp_env = *env;
	fond = 0;
	while (tmp_env)
	{
		fond = check_fond(tmp_env->value);
		if ((ft_strncmp(str, tmp_env->value, check_fond(str)) == 0 \
			&& ft_strncmp(tmp_env->value, str, fond) == 0))
		{
			if (ft_strchr(tmp_env->value, '='))
			{
				free(tmp_env->value);
				tmp_env->value = NULL;
				tmp_env->value = ft_strdup(str);
			}
			return ;
		}
		tmp_env = tmp_env->next;
	}
	get_env(env, str);
}
