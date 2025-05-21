/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_utlis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:28:18 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/21 14:31:51 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	argv_len(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token && token->type <= 3)
			count++;
		else if (token && token->type > 3)
			token = token->next;
		token = token->next;
	}
	if (count == 0)
		count++;
	return (count);
}

void    ft_redirection(t_lexer **lexer, t_token **token)
{
    if ((*token) && (*token)->next)
    {
        append_lexer(lexer, (*token)->next->str, (*token)->type);
        (*token) = (*token)->next;
    }
}
