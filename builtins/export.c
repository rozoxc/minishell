/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:13:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/20 19:15:34 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_export(char **arg, char ***env)
{
    
}
int main()
{
    char *str;

    str = getenv("HOME");
    if (str == NULL)
        perror("getenv fail\n");
    printf("%s\n", str);
}