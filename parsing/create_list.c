/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:20:04 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/21 15:13:52 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_args_and_redirects(t_token **token,
		char **argv, t_lexer **lexer, int *i)
{
	if (*token && (*token)->type <= 3)
		argv[(*i)++] = ft_strdup((*token)->str);
	else if (*token && (*token)->type > 3)
		ft_redirection(lexer, token);
}

int	process_cmd_segment(t_token **token, char **argv, t_lexer **lexer)
{
	int	i;

	i = 0;
	while (*token && (*token)->type != PIPE)
	{
		process_args_and_redirects(token, argv, lexer, &i);
		*token = (*token)->next;
		if ((!(*token) && (argv[0] == NULL && argv[1] == NULL)) \
		|| (*token && (*token)->type == PIPE
				&& (argv[0] == NULL && argv[1] == NULL)))
			argv[0] = ft_strdup(" ");
	}
	return (1);
}

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
		argv[argv_len(token) - 1] = NULL;
		if (!process_cmd_segment(&token, argv, &lexer))
			continue ;
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
