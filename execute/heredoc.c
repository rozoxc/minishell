/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/08 00:33:46 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void process_input(t_obj *obj, char *s, int fd, char *stop)
{
    pid_t pid;
    int status;
    
    pid = fork();
    if (pid == 0)
    {
        process_child(obj, s, fd, stop);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
            get_signal = 1;
    }
}

char *ft_run(t_obj *obj, char *stop, int n)
{
	char *file;
	int fd;
	char *s;

	s = remove_all_quotes(stop);
	while (1)
	{
        file = ft_strjoin2(".f", ft_itoa(n), 3);
        if (access(file, F_OK) != 0)
            break;
        free(file);
        n++;
    }
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	process_input(obj, s, fd, stop);
	if (get_signal || obj->cmd->argv[0] == NULL)
		unlink(file);
	close(fd);
	return (file);
}

void ft_process_heredoc(t_obj *obj, t_lexer *lexer, int index)
{
	char *name;
	
	if (lexer->i == HEREDOC)
	{
		name = ft_run(obj, lexer->str, index);
		if (!get_signal)
		{
			free(lexer->str);
			lexer->str = NULL;
			lexer->str = ft_strdup(name);
			free(name);
		}
	}
}

void ft_heredoc_execution(t_obj *obj, t_cmd *cmd_t, t_lexer *lexer)
{
	int i;
	
	i = 0;
	get_signal = 0;
	while (cmd_t && !get_signal)
	{
		lexer = cmd_t->lexer;
		while (lexer && !get_signal)
		{
			if (lexer->i == HEREDOC)
			{
				ft_process_heredoc(obj, lexer, i);
				i++;
			}
			lexer = lexer->next;
		}
		if (get_signal)
			break;
		cmd_t = cmd_t->next;
	}
}

int	ft_heredoc(t_obj *obj)
{
	t_cmd		*cmd_t;
	t_lexer		*lexer;

	cmd_t = obj->cmd;
	lexer = NULL;
	if (is_heredoc(cmd_t) != 1)
		return (SUCCESS);
	get_signal = 0;
	ft_heredoc_execution(obj, cmd_t, lexer);
	if (get_signal)
		return (FAILURE);
	return (SUCCESS);
}
