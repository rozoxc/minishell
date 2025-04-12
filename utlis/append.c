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