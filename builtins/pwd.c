/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:16:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/02 11:18:17 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_pwd(char **argv, t_obj *obj)
{
    (void)argv;
    
    // If we don't have a cached path yet, initialize it
    if (obj->tool.pwd == NULL)
    {
        char initial_path[PATH_MAX];
        
        if (getcwd(initial_path, sizeof(initial_path)) == NULL)
        {
            perror("getcwd");
            return (FAILURE);
        }
        obj->tool.pwd = strdup(initial_path);
        if (obj->tool.pwd == NULL)
        {
            perror("strdup");
            return (FAILURE);
        }
    }
    
    printf("%s\n", obj->tool.pwd);
    return (SUCCESS);
}
