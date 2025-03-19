/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:03:39 by ababdoul          #+#    #+#             */
/*   Updated: 2025/03/19 05:55:39 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#define MAX_ARG 64

typedef enum t_token_type{
    word; // commande
    pipe; // |
    redirect_in; // <
    redirect_out; // >
    redirect_append; // >>
    heredoc; // <<
}s_token_type;

typedef struct t_cmd{
    char **args;
    int pipe;
    int input_fd;
    int output_fd;
    struct t_cmd *next;
}s_cmd;

typedef struct t_token{
    char *value;
    s_token_type type;
    struct t_token *next;
}s_token;

s_token *lexer(char *input);
#endif