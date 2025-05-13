/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:20 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/13 16:00:53 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_obj *obj, t_cmd *cur_cmd, int fd_pipe[2], char **env)
{
	char	*path;

	path = NULL;
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

void	execution_loop(t_obj *obj, int fd_in, int fd_out, char **env)
{
	t_cmd	*cur_cmd;
	int		pid;
	int		ft_pipe[2];
	t_lexer	*lexer;

	lexer = obj->cmd->lexer;
	cur_cmd = obj->cmd;
	pid = 0;
	obj->pid = malloc(sizeof(t_cmd) * count_cmds(obj));
	while (cur_cmd)
	{
		pipe_error(obj, pipe(ft_pipe));
		obj->pid[pid] = fork_error(obj, fork());
		if (obj->pid[pid] == 0)
		{
			close(fd_in);
			close(fd_out);
			child_process(obj, cur_cmd, ft_pipe, env);
		}
		else
		{
			while (lexer)
			{
				if (lexer->i == HEREDOC)
					close(lexer->fd);
				lexer = lexer->next;
			}
			parent_process(obj, cur_cmd, ft_pipe);
			cur_cmd = cur_cmd->next;
			pid++;
		}
	}
}

int	execute(t_obj *obj)
{
	t_cmd	*cur_cmd;
	int		std_in;
	int		std_out;
	char	**env;

	shift_empty_args_cmds(obj->cmd);
	env = env_to_array(obj->env);
	std_in = dup_error(obj, dup(STDIN_FILENO));
	std_out = dup_error(obj, dup(STDOUT_FILENO));
	cur_cmd = obj->cmd;
	if (ft_heredoc(obj) == FAILURE)
	{
		cleanup_execution(obj, std_in, std_out, env);
		return (determine_exit_code(obj, 1), 1);
	}
	if (cur_cmd && cur_cmd->argv[0] && check_build(cur_cmd->argv[0]) && \
		cur_cmd->next == NULL)
	{
		if (set_redirections(cur_cmd) == Q_ERROR)
		{
			cleanup_execution(obj, std_in, std_out, env);
			return (determine_exit_code(obj, 1), 1);
		}
		run_build(obj, cur_cmd->argv);
	}
	else if (cur_cmd)
	{
		execution_loop(obj, std_in, std_out, env);
		ft_wait_all(obj);
	}
	cleanup_execution(obj, std_in, std_out, env);
	return (130);
}
