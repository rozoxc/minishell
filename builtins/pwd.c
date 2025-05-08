/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:16:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/07 23:19:02 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Create environment variable prefix for searching */
char	*create_env_prefix(char *key, int *prefix_len)
{
	char	*prefix;
	int		i;

	*prefix_len = 0;
	while (key[*prefix_len])
		(*prefix_len)++;
	prefix = malloc(*prefix_len + 2);
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

/* Search for environment variable by key */
char	*search_env_var(t_env *env, char *prefix, int prefix_len)
{
	t_env	*current;
	char	*result;

	current = env;
	while (current)
	{
		if (current->value
			&& ft_strncmp(current->value, prefix, prefix_len + 1) == 0)
		{
			result = current->value + prefix_len + 1;
			free(prefix);
			return (result);
		}
		current = current->next;
	}
	free(prefix);
	return (NULL);
}

/* Get environment variable value by key */
char	*ft_getenv(t_env *env, char *key)
{
	char	*prefix;
	int		prefix_len;

	if (!env || !key)
		return (NULL);
	prefix = create_env_prefix(key, &prefix_len);
	if (!prefix)
		return (NULL);
	return (search_env_var(env, prefix, prefix_len));
}

int	ft_pwd(t_env *env)
{
	char		*buf;
	char		*node;
	static char	*save;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		node = ft_getenv(env, "PWD");
		if (!node)
		{
			printf("%s\n", save);
			return (0);
		}
		save = buf;
		printf("%s\n", node);
	}
	else if (buf)
	{
		printf("%s\n", buf);
		save = buf;
		free(buf);
	}
	return (0);
}
