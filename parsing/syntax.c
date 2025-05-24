/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:42:20 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/24 23:21:16 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirection(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && (!token->next || !token->prev))
			return (-2);
		if (token->type == PIPE && token->next->type == PIPE)
			return (-2);
		if ((token->type == APPEND || token->type == INPUT \
				|| token->type == TRUNC \
				|| token->type == HEREDOC) && (!token->next || \
			token->next->type > ARG))
			return (-3);
		else if ((ft_strchr(token->str, '\"') == NULL && \
				ft_strchr(token->str, '\'') == NULL) && \
				(ft_strnstr(token->str, ">>>", ft_strlen(token->str)) \
				|| ft_strnstr(token->str, "<<<", ft_strlen(token->str))))
			return (-4);
		token = token->next;
	}
	return (SUCCESS);
}

int	syntax(t_token *token)
{
	int	i;

	i = check_redirection(token);
	if (i != 0)
	{
		if (i == -2)
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		else if (i == -3)
			ft_putstr_fd("bash: syntax error near \
unexpected token `newline'\n", 2);
		else if (i == -4)
			ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
