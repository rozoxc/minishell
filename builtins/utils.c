/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:22:24 by hfalati           #+#    #+#             */
/*   Updated: 2025/04/26 15:37:11 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_fond(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (str[i] == ' ' || str[i] == '?')
            return (-1);
        i++;
    }
    if (str[i] == '\0')
        return (i);
    return (i);
}

void add_env(char *str, t_env **env)
{
    t_env *tmp_env;
    int fond;
    
    tmp_env = *env;
    fond = 0;
    while (tmp_env)
    {
        fond = check_fond(tmp_env->value);
        if ((ft_strncmp(str, tmp_env->value, check_fond(str)) == 0 \
            && ft_strncmp(tmp_env->value, str, fond) == 0))
        {
            free(tmp_env->value);
            tmp_env->value = NULL;
            tmp_env->value = ft_strdup(str);
            return ;
        }
        tmp_env = tmp_env->next;
    }
    get_env(env, str);
}