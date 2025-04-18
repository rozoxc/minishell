/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:35:29 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/15 12:05:48 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int len_env(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
        i++;
    return (i);
}
int ft_unset(char **args)
{
    char **env;
    int size;
    int i;

    i = 0;
    size = len_env(args);
    env = malloc(sizeof(char *) * size);
    if (env == NULL)
        return (FAILURE);
    while (args[i] != NULL)
    {
        env[i] = args[i];
        i++;
    }
}
int main(int ac, char **av, char **env)
{
    char **str = {"unset", "HOME", NULL};
    ft_unset(str);
}