/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:39:34 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/01 22:23:47 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_size(char **arg)
{
    int i;
    
    i = 0;
    while (arg[i] != NULL)
        i++;
    return (i);
}

static void echo_print_args(char **arg, int start_idx, int size, int no_new_line)
{
    int i;
    
    i = start_idx;
    while (i < size)
    {
        ft_putstr_fd(arg[i], 1);
        if (i < size - 1)
            write(1, " ", 1);
        i++;
    }
    if (!no_new_line)
        write(1, "\n", 1);
}

int check_flag(char *str)
{
    int i;
    
    if (ft_strcmp(str, "-n") != 0 && ft_strncmp(str, "-n", 2) != 0)
        return (0);
    i = 2;
    while (str[i] != '\0')
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int ft_echo(char **arg, t_obj *obj)
{
    int no_new_line;
    int size;
    int start_idx;
    
    (void)obj;
    size = ft_size(arg);
    no_new_line = 0;
    start_idx = 1;
    
    while (start_idx < size && check_flag(arg[start_idx]))
    {
        no_new_line = 1;
        start_idx++;
    }
    echo_print_args(arg, start_idx, size, no_new_line);
    return (EXIT_SUCCESS);
}
