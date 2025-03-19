/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 05:56:46 by ababdoul          #+#    #+#             */
/*   Updated: 2025/03/19 06:17:32 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

s_token *lexer(char *input)
{
    int i;
    s_token_type type;
    s_token *value;

    value = malloc(sizeof(char) * ft_strlen(input) + 1);
    i = 0;
    while (input[i] != '\0')
    {
        value[i] = input[i];
        i++;
    }
    value[i] = '\0';
}