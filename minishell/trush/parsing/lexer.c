/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozo <rozo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 05:56:46 by ababdoul          #+#    #+#             */
/*   Updated: 2025/03/21 17:42:30 by rozo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void set_operatore(s_token *token, char *str)
{
    if (strcmp(str, "|") == 0)
        token->type = pipe;
    else if (strcmp(str, "<") == 0)
        token->type = redirect_in;
    else if (strcmp(str, ">") == 0)
        token->type = redirect_out;
    else if (strcmp(str, ">>") == 0)
        token->type = redirect_append;
    else if (strcmp(str, "<<") == 0)
        token->type = heredoc;
    else
        token->type = word;
}

s_token *add_new_token(char *str)
{
    s_token *token;

    token = malloc(sizeof(s_token));
    if (token == NULL)
        return NULL;
    token->value = strdup(str);
    token->next = NULL;
    return (token);
}

s_token *lexer(char *input)
{
    int i;
    s_token *token;
    s_token *head;
    s_token *current;
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

int main()
{
    s_token *token;
    char *str = "cat file.txt | grep \"abdou\"";

    token = lexer(str);
    while (token != NULL)
    {
        printf("token : %s and type : %d\n", token->value, token->type);
        token = token->next;
    }
    return (0);
}
