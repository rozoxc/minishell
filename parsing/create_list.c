/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:20:04 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/06 11:39:59 by hfalati          ###   ########.fr       */
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
		{
			count++;
		}
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

t_cmd	*creat_list_loop(t_token *token, t_cmd *cmd, \
			t_lexer *lexer, char **argv)
{
	int	i;
	int fd;

	while (token)
	{
		lexer = NULL;
		argv = (char **)malloc(sizeof(char *) * (argv_len(token) + 1));
		if (!argv)
			return (NULL);
		argv[argv_len(token)] = NULL;
		i = 0;
		while (token && token->type != PIPE)
		{
			if (token && token->type <= 3)
				argv[i++] = ft_strdup(token->str);
			else if ((token && token->type > 3 && argv[0] != NULL) || (token && token->type == HEREDOC))
				ft_redirection(&lexer, &token);
			token = token->next;
			if (token && token->type == ARG && argv[0] == NULL)
			{
				if (token->str[0] == '\0' && (!ft_strchr(++token->str, '"') && !ft_strchr(token->str, '\'')))
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(token->str, 2);
					token->str--;
					ft_putstr_fd(": ambiguous redirect\n", 2);
					continue;
				}
				token->str--;
				if (token->str[0] == '\0' && (ft_strchr(++token->str, '"') || ft_strchr(token->str, '\'')))
				{
					token->str--;
					ft_putstr_fd("minishell: : No such file or directory\n", 2);
					continue;
				}
				fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
				close(fd);
				token = token->next;
			}
			if (token && token->type == PIPE && argv[0] == NULL)
				token = token->next;
		}
		append_argv(&cmd, lexer, argv);
		if (token)
			token = token->next;
	}
	return (cmd);
}

t_cmd	*create_list(t_obj *obj)
{
	t_cmd	*cmd;
	t_lexer	*lexer;
	char	**argv;

	cmd = NULL;
	lexer = NULL;
	argv = NULL;
	return (creat_list_loop(obj->token, cmd, lexer, argv));
}
