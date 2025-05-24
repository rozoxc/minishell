/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:22:24 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/24 23:29:04 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_fond(char *str)
{
	int	i;
	int	count;

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
			if (ft_strchr(str, '='))
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

int	check_export_syntax(char **av, int i, t_obj *obj)
{
	int	pos;

	pos = 0;
	if (!is_valid_varname_char(av[i][0], 1))
	{
		export_error(av[i], obj);
		return (FAILURE);
	}
	while (av[i][pos] != '\0' && av[i][pos] != '=' && av[i][pos] != '+')
	{
		if (!is_valid_varname_char(av[i][pos], 0))
			return (export_error(av[i], obj), FAILURE);
		pos++;
	}
	if (ft_strnstr(av[i], "+=", ft_strlen(av[i])))
	{
		pos = ft_strchr(av[i], '+') - av[i];
		if (pos > 0 && av[i][pos - 1] != '+' && av[i][pos + 1] == '=')
			return (determine_exit_code(obj, 0), SUCCESS);
		return (export_error(av[i], obj), FAILURE);
	}
	if (ft_strchr(av[i], '=') || av[i][pos] == '\0')
		return (determine_exit_code(obj, 0), SUCCESS);
	export_error(av[i], obj);
	return (FAILURE);
}

int	handle_export_args(char **av, t_obj *obj, int *count)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_export_syntax(av, i, obj) == SUCCESS)
		{
			if (process_export_arg(av[i], obj) == FAILURE)
				determine_exit_code(obj, 1);
		}
		else
		{
			determine_exit_code(obj, 1);
			(*count)++;
		}
		i++;
	}
	return (SUCCESS);
}

void	swap_strings(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}
