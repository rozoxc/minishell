/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:20:04 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/07 22:34:43 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function to process arguments and redirections */
void	process_args_and_redirects(t_token **token,
		char **argv, t_lexer **lexer, int *i)
{
	if (*token && (*token)->type <= 3)
		argv[(*i)++] = ft_strdup((*token)->str);
	else if ((*token && (*token)->type > 3 && argv[0] != NULL)
		|| (*token && (*token)->type == HEREDOC))
		ft_redirection(lexer, token);
}

/* Function to handle special token cases */
void	handle_special_token(t_token **token)
{
	if ((*token)->str[0] == '\0' && (!ft_strchr(++(*token)->str, '"')
			&& !ft_strchr((*token)->str, '\'')))
	{
		handle_ambiguous_redirect(*token);
		return ;
	}
	(*token)->str--;
	if ((*token)->str[0] == '\0' && (ft_strchr(++(*token)->str, '"')
			|| ft_strchr((*token)->str, '\'')))
	{
		(*token)->str--;
		handle_no_such_file();
		return ;
	}
	handle_file_open(*token);
	*token = (*token)->next;
}

/* Function to process each command segment */
int	process_cmd_segment(t_token **token, char **argv, t_lexer **lexer)
{
	int	i;

	i = 0;
	while (*token && (*token)->type != PIPE)
	{
		process_args_and_redirects(token, argv, lexer, &i);
		*token = (*token)->next;
		if (*token && (*token)->type == ARG && argv[0] == NULL)
		{
			handle_special_token(token);
			continue ;
		}
		if (*token && (*token)->type == PIPE && argv[0] == NULL)
			*token = (*token)->next;
	}
	return (1);
}

/* Main loop function for creating command list */
t_cmd	*creat_list_loop(t_token *token, t_cmd *cmd, t_lexer *lexer
		, char **argv)
{
	while (token)
	{
		lexer = NULL;
		argv = (char **)malloc(sizeof(char *) * (argv_len(token) + 1));
		if (!argv)
			return (NULL);
		argv[argv_len(token)] = NULL;
		if (!process_cmd_segment(&token, argv, &lexer))
			continue ;
		append_argv(&cmd, lexer, argv);
		if (token)
			token = token->next;
	}
	return (cmd);
}

/* Function to create the command list */
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
