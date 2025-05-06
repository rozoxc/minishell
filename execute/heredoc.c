/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/06 13:50:54 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_input_line(t_obj *obj, char *str, int fd, char *stop)
{
	if (ft_strchr(stop, '\'') || ft_strchr(stop, '"'))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	else
	{
		str = ft_expand(obj, str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
}

void	process_input(t_obj *obj, char *s, int fd, char *stop)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL || ft_strcmp(str, s) == 0)
		{
			free(str);
			close(fd);
			free(s);
			break ;
		}
		write_input_line(obj, str, fd, stop);
	}
}

char	*ft_run(t_obj *obj, char *stop, int n)
{
	char	*file;
	int		fd;
	char	*s;

	s = remove_all_quotes(stop);
	file = ft_strjoin2(".f", ft_itoa(n), 3);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	process_input(obj, s, fd, stop);
	if (obj->cmd->argv[0] == NULL)
		unlink(file);
	close(fd);
	return (file);
}

void	ft_herdoc_execution(t_obj *obj, t_cmd *cmd_t, t_lexer *lexer)
{
	int		i;
	char	*name;

	i = 0;
	while (cmd_t)
	{
		name = NULL;
		lexer = cmd_t->lexer;
		while (lexer)
		{
			if (lexer->i == HEREDOC)
			{
				name = ft_run(obj, lexer->str, i);
				free(lexer->str);
				lexer->str = NULL;
				lexer->str = ft_strdup(name);
				free(name);
				i++;
			}
			lexer = lexer->next;
		}
		cmd_t = cmd_t->next;
	}
}

int	ft_heredoc(t_obj *obj)
{
	t_cmd	*cmd_t;
	t_lexer	*lexer;

	cmd_t = obj->cmd;
	lexer = NULL;
	if (is_heredoc(cmd_t) != 1)
		return (SUCCESS);
	ft_herdoc_execution(obj, cmd_t, lexer);
	return (SUCCESS);
}
