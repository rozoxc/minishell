/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:04:37 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/17 15:40:38 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes(char *str)
{
	char	c;

	c = 0;
	skip_space(&str);
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (*str == '\0')
			{
				printf("minishell: syntax error with open quotes\n");
				return (FAILURE);
			}
		}
		str++;
	}
	return (SUCCESS);
}

char	*get_token(char **str)
{
	char	*line;
	int		i;
	char	c;

	i = 0;
	c = 0;
	line = (char *)malloc(alloc_mem(*str) + 1);
	if (!line)
		return (NULL);
	while (*(*str))
	{
		if (*(*str) == '\"' || *(*str) == '\'')
			c = set_char(str, c);
		line[i] = *(*str);
		i++;
		if (check_sep(str, c) != 0)
			break ;
		(*str)++;
	}
	line[i] = '\0';
	return (line);
}

void	token_type(t_token **token, t_obj *obj)
{
	t_token	*token_tmp;

	token_tmp = *token;
	while (token_tmp->next)
		token_tmp = token_tmp->next;
	if (ft_strcmp(token_tmp->str, "") == 0)
		token_tmp->type = EMPTY;
	else if (ft_strcmp(token_tmp->str, "|") == 0)
		exit_code_pipe(obj, token_tmp);
	else if (ft_strcmp(token_tmp->str, ">") == 0)
		token_tmp->type = TRUNC;
	else if (ft_strcmp(token_tmp->str, "<") == 0)
		token_tmp->type = INPUT;
	else if (ft_strcmp(token_tmp->str, ">>") == 0)
		token_tmp->type = APPEND;
	else if (ft_strcmp(token_tmp->str, "<<") == 0)
		token_tmp->type = HEREDOC;
	else if (token_tmp->prev == NULL || token_tmp->prev->type == PIPE)
		token_tmp->type = COMMAND;
	else if (token_tmp->prev->prev && token_tmp->prev->prev->type == HEREDOC)
		token_tmp->type = COMMAND;
	else
		token_tmp->type = ARG;
}

t_token	*token(char **str, t_obj *obj)
{
	t_token	*token;
	char	*line;

	line = NULL;
	token = NULL;
	while (*(*str))
	{
		skip_space(str);
		line = get_token(str);
		append_token(&token, line);
		token_type(&token, obj);
		free(line);
		line = NULL;
		if (*(*str) == '\0')
			break ;
		(*str)++;
		skip_space(str);
	}
	return (token);
}

int	parsing(t_obj *obj)
{
	char	*str;

	str = obj->str;
	if (str == NULL || is_only_whitespace(str))
	{
		return (determine_exit_code(obj, SUCCESS));
	}
	else if (quotes(str) == FAILURE)
		return (determine_exit_code(obj, SYNTAX_ERRROR));
	obj->token = token(&str, obj);
	if (syntax(obj->token) == FAILURE)
	{
		free_token(&obj->token);
		return (determine_exit_code(obj, SYNTAX_ERRROR));
	}
	expand(obj);
	obj->cmd = create_list(obj);
	free_token(&obj->token);
	if (obj->cmd != NULL)
		return (determine_exit_code(obj, SUCCESS));
	return (determine_exit_code(obj, 0));
}
