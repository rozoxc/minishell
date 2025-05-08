/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_utlis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:28:18 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/07 22:32:05 by ababdoul         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token->str, 2);
	token->str--;
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

void	handle_no_such_file(void)
{
	ft_putstr_fd("minishell: : No such file or directory\n", 2);
}
