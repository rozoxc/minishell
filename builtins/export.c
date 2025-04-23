/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/23 12:51:47 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_export(char **av, t_obj *obj)
{
    int i;
    int fond;

    i = 1;
    fond = 0;
    while (av[i])
    {
        fond = check_fond(av[i]);
        if (fond == -1)
        {
            printf("export: not avalid in this context: %s\n", av[i]);
            return (FAILURE);
        }
        else if (fond != 0)
            add_env(av[i], &obj->env);
        i++;
    }
    return (SUCCESS);
}
