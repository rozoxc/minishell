/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:16:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/03 12:21:12 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_getenv(t_env *env, char *key)
{
    t_env *current;
    char *prefix;
    int prefix_len;
    
    if (!env || !key)
        return (NULL);
    prefix_len = 0;
    while (key[prefix_len])
        prefix_len++;
    prefix = malloc(prefix_len + 2);
    if (!prefix)
        return (NULL);
    int i = 0;
    while (key[i])
    {
        prefix[i] = key[i];
        i++;
    }
    prefix[i] = '=';
    prefix[i + 1] = '\0';
    current = env;
    while (current)
    {
        if (current->value && ft_strncmp(current->value, prefix, prefix_len + 1) == 0)
        {
            free(prefix);
            return (current->value + prefix_len + 1);
        }
        current = current->next;
    }
    
    free(prefix);
    return (NULL);
}

int ft_pwd(t_env *env)
{
    char    *buf;
    char   *node;
    static char *save;

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
