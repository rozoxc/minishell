#include "../includes/minishell.h"

int	alloc_mem(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			c = *str;
		i++;
		if (check_sep(&str, c) != 0)
			break ;
		str++;
	}
	return (i);
}

void	append_token(t_token **token, char *str)
{
	t_token	*tmp_token;

	tmp_token = *token;
	if (!tmp_token)
	{
		(*token) = malloc(sizeof(t_token));
		if (!token)
			return ;
		(*token)->str = ft_strdup(str);
		(*token)->next = NULL;
		(*token)->prev = NULL;
	}
	else
	{
		while (tmp_token->next)
			tmp_token = tmp_token->next;
		tmp_token->next = malloc(sizeof(t_token));
		if (!tmp_token->next)
			return ;
		tmp_token->next->prev = tmp_token;
		tmp_token->next->str = ft_strdup(str);
		tmp_token->next->next = NULL;
	}
}

void	append_lexer(t_lexer **lexer, char *str, int i)
{
	t_lexer	*tmp_cmd;

	tmp_cmd = *lexer;
	if (!tmp_cmd)
	{
		(*lexer) = malloc(sizeof(t_lexer));
		if (!*lexer)
			return ;
		(*lexer)->str = ft_strdup(str);
		(*lexer)->i = i;
		(*lexer)->next = NULL;
	}
	else
	{
		while (tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		tmp_cmd->next = malloc(sizeof(t_lexer));
		if (!tmp_cmd->next)
			return ;
		tmp_cmd->next->str = ft_strdup(str);
		tmp_cmd->next->i = i;
		tmp_cmd->next->next = NULL;
	}
}

void	append_argv(t_cmd **cmd, t_lexer *lexer, char **argv)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = *cmd;
	if (!tmp_cmd)
	{
		(*cmd) = malloc(sizeof(t_cmd));
		if (!*cmd)
			return ;
		(*cmd)->argv = argv;
		(*cmd)->lexer = lexer;
		(*cmd)->next = NULL;
		(*cmd)->prev = NULL;
	}
	else
	{
		while (tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		tmp_cmd->next = malloc(sizeof(t_cmd));
		if (!tmp_cmd->next)
			return ;
		tmp_cmd->next->argv = argv;
		tmp_cmd->next->lexer = lexer;
		tmp_cmd->next->next = NULL;
		tmp_cmd->next->prev = tmp_cmd;
	}
}