/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 08:57:55 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/09 13:07:00 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// bda khadma mihim nta 3araf sir shof include do struct rah ma3rofin chra7hom chatgpt khadi ichrah lik kola struct wlach lay9a mohim bda tparsi f token nta tama

#include "../includes/minishell.h"

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *cmd_list;
    t_cmd *last_cmd;
    t_cmd *new_cmd;
    t_token *current;
    t_token *tmp;
    int ac;
    int i;

    cmd_list = NULL;
    last_cmd = NULL;
    current = tokens;
    while (current != NULL)
    {
        ac = 0;
        tmp = current;
        while (tmp != NULL && tmp->type != PIPE)
        {
            ac++;
            tmp = tmp->next;
        }
        new_cmd = malloc(sizeof(t_cmd));
        new_cmd->argv = malloc(sizeof(char *) * (ac + 1));
        i = 0;
        while (i < ac)
        {
            new_cmd->argv[i] = strdup(current->str);
            i++;
            current = current->next;
        }
        new_cmd->argv[i] = NULL;
        if (current && current->type == PIPE)
            current = current->next;
        new_cmd->next = NULL;
        new_cmd->prev = last_cmd;
        if (last_cmd == NULL)
            cmd_list = new_cmd;
        else
            last_cmd->next = new_cmd;
        last_cmd = new_cmd;
    }
    return (cmd_list);
}