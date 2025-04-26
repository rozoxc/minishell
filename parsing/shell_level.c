/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:40:26 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/26 15:29:04 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void shell_level(t_obj *obj)
{
   char *shell_level;
   int level;
   char *new_level;
   char *str;
   
   shell_level = getenv("SHLVL");
   if (shell_level == NULL)
        level = 1;
    else
        level = ft_atoi(shell_level) + 1;
    new_level = ft_itoa(level);
    if (new_level == NULL)
        perror("error!\n");
    str = ft_strdup("SHLVL=");
    str = ft_strjoin2(str, new_level, 1);
    add_env(str, &obj->env);
    free(str);
    free(new_level);
}