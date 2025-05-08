/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/08 16:14:48 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_input(t_obj *obj, char *s, int fd, char *stop)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		process_child(obj, s, fd, stop);
	else
	{
		free(s);
		waitpid(pid, &status, 0);
		signal(SIGINT, SIG_DFL);
		if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
			obj->status = 1;
	}
}

char	*ft_run(t_obj *obj, char *stop, int n)
{
	char	*file;
	int		fd;
	char	*s;

	s = remove_all_quotes(stop);
	if (ft_strchr(stop, '$'))
		adjust_dollars(s);
	while (1)
	{
		file = ft_strjoin2(".f", ft_itoa(n), 3);
		if (access(file, F_OK) != 0)
			break ;
		free(file);
		n++;
	}
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	process_input(obj, s, fd, stop);
	if (obj->status || obj->cmd->argv[0] == NULL)
		unlink(file);
	close(fd);
	return (file);
}

void	ft_process_heredoc(t_obj *obj, t_lexer *lexer, int index)
{
	char	*name;

	if (lexer->i == HEREDOC)
	{
		name = ft_run(obj, lexer->str, index);
		free(lexer->str);
		lexer->str = NULL;
		if (!obj->status)
			lexer->str = ft_strdup(name);
		free(name);
	}
}

void	ft_heredoc_execution(t_obj *obj, t_cmd *cmd_t, t_lexer *lexer)
{
	int	i;

	i = 0;
	while (cmd_t && !obj->status)
	{
		lexer = cmd_t->lexer;
		while (lexer && !obj->status)
		{
			if (lexer->i == HEREDOC)
			{
				ft_process_heredoc(obj, lexer, i);
				i++;
			}
			lexer = lexer->next;
		}
		if (obj->status)
			break ;
		cmd_t = cmd_t->next;
	}
}

int	ft_heredoc(t_obj *obj)
{
	t_cmd		*cmd_t;
	t_lexer		*lexer;

	obj->status = 0;
	cmd_t = obj->cmd;
	lexer = NULL;
	if (is_heredoc(cmd_t) != 1)
		return (SUCCESS);
	ft_heredoc_execution(obj, cmd_t, lexer);
	if (obj->status)
		return (FAILURE);
	return (SUCCESS);
}
