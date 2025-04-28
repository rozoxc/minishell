/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:35:29 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/27 22:02:12 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	is_valid_env_key(const char *key)
{
	int	i;

	if (!key || !*key || ft_isdigit(*key))
		return (0);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_node(t_env **env_list, t_env *to_remove)
{
	if (!env_list || !*env_list || !to_remove)
		return ;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	else
		*env_list = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	free(to_remove->value);
	free(to_remove);
}

static void	process_unset_arg(t_obj *obj, char *arg, int *ret)
{
	size_t	key_len;
	t_env	*current;
	t_env	*next;

	if (!is_valid_env_key(arg))
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		*ret = 1;
		return ;
	}
	key_len = ft_strlen(arg);
	current = obj->env;
	while (current)
	{
		next = current->next;
		if (ft_strncmp(current->value, arg, key_len) == 0 && \
			(current->value[key_len] == '=' || current->value[key_len] == '\0'))
		{
			remove_env_node(&obj->env, current);
		}
		current = next;
	}
}

int	ft_unset(char **args, t_obj *obj)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		process_unset_arg(obj, args[i], &ret);
		i++;
	}
	return (ret);
}
