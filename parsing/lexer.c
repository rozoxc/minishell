/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozox <rozox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 05:56:46 by ababdoul          #+#    #+#             */
/*   Updated: 2025/03/21 05:35:28 by rozox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

s_token *add_new_token(char *str)
{
    s_token *token;

    token = malloc(sizeof(s_token));
    if (token != NULL)
        return NULL;
    token->value = ft_strdup(str);
    token->next = NULL;
    return (token);
 }

s_token *lexer(char *input)
{
    int i;
    s_token_type type;
    s_token *token;
    s_token *head;
    s_token *current;
    char **str;

    head = NULL;
    current = NULL;
    if (token == NULL)
        return NULL;
    str = ft_split(input, ' ');
    i = 0;
    while (str[i] != NULL)
    {
        token = add_new_token(str[i]);
        if (token == NULL)
            return NULL;
        if (head == NULL)
            head = token;
        else
            current->next = token;
        current = token;
        i++;
    }
    return (head);
}
int main()
{
    s_token *token;
    char *str = "ls -la";

    token  = lexer(str);
    while (token != NULL)
    {
        printf("token : %s\n", token->value);
        token = token->next;
    }
    return (0);
}