/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_utlis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:28:18 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/19 12:54:08 by hfalati          ###   ########.fr       */
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
	return (count);
}

void	ft_redirection(t_lexer **lexer, t_token **token)
{
	if ((*token) && (*token)->next)
	{
		append_lexer(lexer, (*token)->next->str, (*token)->type);
		(*token) = (*token)->next;
	}
}

void	handle_file_open(t_token *token)
{
	int	fd;

	fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	close(fd);
}

void	handle_ambiguous_redirect(t_token *token)
{
	token->str--;
	ft_putstr_fd("minishell: ambiguous redirect\n", 2);
}
