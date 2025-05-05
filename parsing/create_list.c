/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:20:04 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/05 11:34:05 by hfalati          ###   ########.fr       */
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

t_cmd	*creat_list_loop(t_obj *obj, t_cmd *cmd, \
			t_lexer *lexer, char **argv)
{
	int	i;
	int fd;

	while (obj->token)
	{
		lexer = NULL;
		argv = (char **)malloc(sizeof(char *) * (argv_len(obj->token) + 1));
		if (!argv)
			return (NULL);
		argv[argv_len(obj->token)] = NULL;
		i = 0;
		while (obj->token && obj->token->type != PIPE)
		{
			if (obj->token && obj->token->type <= 3)
				argv[i++] = ft_strdup(obj->token->str);
			else if ((obj->token && obj->token->type > 3 && argv[0] != NULL) || (obj->token && obj->token->type == HEREDOC))
				ft_redirection(&lexer, &obj->token);
			obj->token = obj->token->next;
			if (obj->token && obj->token->type == ARG && argv[0] == NULL)
			{
				if (obj->token->str[0] == '\0' && (!ft_strchr(++obj->token->str, '"') && !ft_strchr(obj->token->str, '\'')))
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(obj->token->str, 2);
					obj->token->str--;
					ft_putstr_fd(": ambiguous redirect\n", 2);
					determine_exit_code(obj, 1);
					return (NULL);
				}
				obj->token->str--;
				if (obj->token->str[0] == '\0' && (ft_strchr(++obj->token->str, '"') || ft_strchr(obj->token->str, '\'')))
				{
					obj->token->str--;
					ft_putstr_fd("minishell: : No such file or directory\n", 2);
					determine_exit_code(obj, 1);
					return (NULL);
				}
				obj->token->str--;
				fd = open(obj->token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
				close(fd);
				obj->token = obj->token->next;
			}
			if (obj->token && obj->token->type == PIPE && argv[0] == NULL)
				obj->token = obj->token->next;
		}
		append_argv(&cmd, lexer, argv);
		if (obj->token)
			obj->token = obj->token->next;
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
	return (creat_list_loop(obj, cmd, lexer, argv));
}
