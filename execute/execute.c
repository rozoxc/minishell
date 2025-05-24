/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:20 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/24 23:49:38 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_obj *obj, t_cmd *cur_cmd, int fd_pipe[2], char **env)
{
	char	*path;

	path = NULL;
	signal(SIGINT, signal_child);
	close(fd_pipe[0]);
	if (cur_cmd->next != NULL)
	{
		dup2_error(obj, dup2(fd_pipe[1], STDOUT_FILENO));
		close(fd_pipe[1]);
		close(fd_pipe[0]);
	}
	if (set_redirections(cur_cmd) == Q_ERROR)
		exit(determine_exit_code(obj, 1));
	if (cur_cmd->argv[0] && check_build(cur_cmd->argv[0]))
		run_build(obj, cur_cmd->argv);
	else
		child_process_execution(obj, path, cur_cmd, env);
	exit(determine_exit_code(obj, 130));
}

void	handle_parent(t_obj *obj, t_cmd **cur_cmd,
	int *pid, int *ft_pipe)
{
	t_lexer	*lexer;

	lexer = obj->cmd->lexer;
	while (lexer)
	{
		if (lexer->i == HEREDOC)
			close(lexer->fd);
		lexer = lexer->next;
	}
	parent_process(obj, *cur_cmd, ft_pipe);
	*cur_cmd = (*cur_cmd)->next;
	(*pid)++;
}

int	process_command(t_obj *obj, t_cmd *cur_cmd,
			int *pid, char **env)
{
	int		ft_pipe[2];
	int		child_pid;

	if (pipe_error(obj, pipe(ft_pipe)) == -1)
		return (-1);
	child_pid = fork_error(obj, fork());
	if (child_pid == -1)
	{
		close(ft_pipe[0]);
		close(ft_pipe[1]);
		return (-1);
	}
	obj->pid[*pid] = child_pid;
	if (child_pid == 0)
	{
		close(obj->fd_in);
		close(obj->fd_out);
		obj->flag = 1;
		child_process(obj, cur_cmd, ft_pipe, env);
	}
	else
		handle_parent(obj, &cur_cmd, pid, ft_pipe);
	return (0);
}

void	execution_loop(t_obj *obj, int fd_in, int fd_out, char **env)
{
	t_cmd	*cur_cmd;
	int		pid;

	cur_cmd = obj->cmd;
	pid = 0;
	signal(SIGINT, SIG_IGN);
	obj->fd_in = fd_in;
	obj->fd_out = fd_out;
	obj->pid = malloc(sizeof(t_cmd) * count_cmds(obj));
	if (!obj->pid)
		return ;
	while (cur_cmd)
	{
		if (process_command(obj, cur_cmd, &pid, env) == -1)
			break ;
		cur_cmd = cur_cmd->next;
	}
}

int	execute(t_obj *obj)
{
	t_cmd	*cur_cmd;
	int		std_in;
	int		std_out;
	char	**env;

	if (setup_execution(obj, &std_in, &std_out, &env) == 1)
		return (1);
	cur_cmd = obj->cmd;
	shift_empty_args_cmds(obj->cmd);
	if (cur_cmd && cur_cmd->argv[0] && check_build(cur_cmd->argv[0]) \
		&& cur_cmd->next == NULL)
	{
		if (set_redirections(cur_cmd) == Q_ERROR)
		{
			return (cleanup_execution(obj, std_in, std_out, env), 1);
		}
		run_build(obj, cur_cmd->argv);
	}
	else if (cur_cmd)
	{
		execution_loop(obj, std_in, std_out, env);
		ft_wait_all(obj);
	}
	cleanup_execution(obj, std_in, std_out, env);
	return (0);
}
