/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:53 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/23 12:15:40 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void update_env(t_obj *obj)
{
    char *pwd;
    char *oldpwd;
    
    pwd = ft_strdup("pwd=");
    oldpwd = ft_strdup("OLDPWD=");
    pwd = ft_strjoin2(pwd, obj->tool.pwd, 1);
    oldpwd = ft_strjoin2(oldpwd, obj->tool.oldpwd, 1);
    add_env(pwd, &obj->env);
    add_env(oldpwd, &obj->env);
    free(pwd);
    free(oldpwd);
}

void swap_path(char **s1, char **s2)
{
    char *tmp;

    tmp = ft_strdup(*s1);
    free(*s1);
    *s1 = ft_strdup(*s2);
    free(*s2);
    *s2 = ft_strdup(tmp);
}

int ft_chdir(char *path)
{
    if (chdir(path) != 0)
    {
        printf("cd: no such file or directory: %s\n", path);
        return (FAILURE);
    }
    return (SUCCESS);
}

int ft_cd(char **av, t_obj *obj)
{
    if (av[1] == NULL)
        return (SUCCESS);
    else if (av[2] != NULL)
    {
        printf("cd: no such file or derectory: %s\n", av[1]);
        return (FAILURE);
    }
    if (ft_strcmp(av[1], "-") == 0)
    {
        if (ft_chdir(obj->tool.oldpwd) == FAILURE)
            return (FAILURE);
        swap_path(&obj->tool.oldpwd, &obj->tool.pwd);
    }
    else
    {
        if (ft_chdir(av[1]) == FAILURE)
            return (FAILURE);
        free(obj->tool.oldpwd);
        obj->tool.oldpwd = ft_strdup(obj->tool.pwd);
        free(obj->tool.pwd);
        obj->tool.pwd = ft_strdup(av[1]);
    }
    update_env(obj);
    return (SUCCESS);
}