/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozox <rozox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 05:33:28 by rozox             #+#    #+#             */
/*   Updated: 2025/03/21 05:35:11 by rozox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

char *ft_strdup(char *str)
{
    int i;
    char *p;

    i = 0;
    p = malloc(sizeof(char) * ft_strlen(str) + 1);
    if (p == NULL)
        return NULL;
    while (str[i] != '\0')
    {
        p[i] = str[i];
        i++;
    }
    p[i] = '\0';
}