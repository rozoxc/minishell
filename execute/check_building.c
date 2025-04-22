/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_building.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:15:34 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/22 10:11:12 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int run_build(t_obj *obj, char **cmd, char **env)
{
    if (ft_strcmp(cmd[0], "echo") == 0)
        ft_echo(cmd, obj);
    else if (ft_strcmp(cmd[0], "pwd") == 0)
        ft_pwd(cmd, obj);
    else if (ft_strcmp(cmd[0], "env") == 0)
        ft_env(env);
    else if (ft_strcmp(cmd[0], "cd") == 0)
        ft_cd(cmd);
    else if (ft_strcmp(cmd[0], "exit") == 0)
        ft_exit(cmd);
    return (obj->exit_code);
}
int check_build(char *cmd)
{
    if (cmd == NULL)
        return (0);
    return (
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "cd")  == 0||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "unset") == 0||
        ft_strcmp(cmd, "env") == 0||
        ft_strcmp(cmd, "exit") == 0||
        ft_strcmp(cmd, "export") == 0
    );
    return (0);
}