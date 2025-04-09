/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 05:56:46 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/09 13:13:27 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void set_operatore(t_token *token, char *str)
{
    if (strcmp(str, "|") == 0)
        token->type = PIPE;
    else if (strcmp(str, "<") == 0)
        token->type = REDIRECT_IN;
    else if (strcmp(str, ">") == 0)
        token->type = REDIRECT_OUT;
    else if (strcmp(str, ">>") == 0)
        token->type = REDIRECT_APPEND;
    else if (strcmp(str, "<<") == 0)
        token->type = HEREDOC;
    else
        token->type = WORD;
}

t_token *add_new_token(char *str)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (token == NULL)
        return NULL;
    token->str = strdup(str);
    token->next = NULL;
    return (token);
}

t_token *lexer(char *input)
{
    int i;
    t_token *token;
    t_token *head;
    t_token *current;
    char **str;

    head = NULL;
    current = NULL;

    str = ft_split(input, ' ');
    if (!str)
        return NULL;
    i = 0;
    while (str[i] != NULL)
    {
        token = add_new_token(str[i]);
        if (token == NULL)
            return NULL;
        set_operatore(token, str[i]);
        if (head == NULL)
            head = token;
        else
            current->next = token;
        current = token;
        i++;
    }
    return (head);
}