/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:16:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/17 02:54:22 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_env_prefix(char *key, int *key_len)
{
	char	*prefix;
	int		i;

	*key_len = 0;
	while (key[*key_len])
		(*key_len)++;
	prefix = malloc(*key_len + 2);
	if (!prefix)
		return (NULL);
	i = 0;
	while (key[i])
	{
		prefix[i] = key[i];
		i++;
	}
	prefix[i] = '=';
	prefix[i + 1] = '\0';
	return (prefix);
}

char	*search_env_var(t_env *env, char *prefix, int key_len)
{
	t_env	*current;
	char	*result;

	current = env;
	while (current)
	{
		if (current->value
			&& ft_strncmp(current->value, prefix, key_len + 1) == 0)
		{
			result = current->value + key_len + 1;
			free(prefix);
			return (result);
		}
		current = current->next;
	}
	free(prefix);
	return (NULL);
}

char	*ft_getenv(t_env *env, char *key)
{
	char	*prefix;
	int		key_len;

	if (!env || !key)
		return (NULL);
	prefix = create_env_prefix(key, &key_len);
	if (!prefix)
		return (NULL);
	return (search_env_var(env, prefix, key_len));
}

int	ft_pwd(t_env *env, t_obj *obj)
{
	char		*buf;
	char		*node;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		node = ft_getenv(env, "PWD");
		if (!node)
		{
			ft_putstr_fd("minishell: PWD not set", 2);
			return (determine_exit_code(obj, 1), 1);
		}
		printf("%s\n", node);
	}
	else if (buf)
	{
		printf("%s\n", buf);
		free(buf);
	}
	return (determine_exit_code(obj, 0), 0);
}
