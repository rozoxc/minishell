/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozox <rozox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 05:56:46 by ababdoul          #+#    #+#             */
/*   Updated: 2025/03/21 05:03:09 by rozox            ###   ########.fr       */
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
s_token *add_new_token()
{
    s_token *token;

    token = malloc(sizeof(s_token));
 }

s_token *lexer(char *input)
{
    int i;
    s_token_type type;
    s_token *token;
    char **str;

    token = malloc(sizeof(s_token));
    if (token == NULL)
        return NULL;
    str = ft_split(input, ' ');
    i = 0;
    while (str[i] != NULL)
    {
        token->value = str[i];
        token->next = add_new_token()
        i++;
    }
}
int main()
{
    s_token *token;
    char *str = "ls -la";

    token  = lexer(str);
    while (token != NULL)
    {
        printf("%s\n", token->value);
        token = token->next;
    }
    return (0);
}