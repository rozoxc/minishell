/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:20 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/10 14:06:05 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_command_path(t_obj *obj, char *cmd)
{
	char *path;

	// if (!cmd || cmd[0] == '\0')
	// {
	// 	ft_putstr_fd("minishell: : command not found\n", 2);
	//     exit(determine_exit_code(obj, 0));
	// }
	if (cmd[0] == '.' && cmd[1] == '/')
		path = ft_strdup(cmd);
	else if (cmd[0] == '/')
		path = ft_strdup(cmd);
	else
	{
		path = get_path(obj, cmd);
		if (path == NULL)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(determine_exit_code(obj, 127));
		}
	}
	return (path);
}

void shift_empty_args(char *argv[])
{
	int	skip;

	skip = 0;
	while (argv[skip] != NULL && argv[skip][0] == '\0')
		skip++;
	if (skip > 0)
	{
		int i = 0;
		while (argv[skip + i] != NULL)
		{
			argv[i] = argv[skip + i];
			i++;
		}
		argv[i] = NULL;
	}
}

void shift_empty_args_cmds(t_cmd *cmd)
{
	t_cmd *current;
	
	current = cmd;
	while (current != NULL)
	{
		if (current->argv != NULL)
		shift_empty_args(current->argv);
		current = current->next;
	}
}

void child_process_execution(t_obj *obj, char *path, t_cmd *cur_cmd, char **env)
{
	if (cur_cmd->argv[0] == NULL && (ft_strchr(obj->str, '"') || ft_strchr(obj->str, '\'')))
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		exit(determine_exit_code(obj, 127));
	}
	else if (cur_cmd->argv[0][0] == '\0' && !cur_cmd->argv[1])
	{
		exit(determine_exit_code(obj, 0));
	}
	path = get_command_path(obj, cur_cmd->argv[0]);
	if (execve(path, cur_cmd->argv, env) == -1)
		handle_execution_error(obj, cur_cmd->argv[0], path, env);
}

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

void	parent_process(t_obj *obj, t_cmd *curr_cmd, int fd_pipe[2])
{
	close(fd_pipe[1]);
	if (curr_cmd->next == NULL)
	{
		close(fd_pipe[0]);
		close(STDIN_FILENO);
	}
	else
	{
		dup2_error(obj, dup2(fd_pipe[0], STDIN_FILENO));
		close(fd_pipe[0]);
	}
}

void	execution_loop(t_obj *obj, int fd_in, int fd_out, char **env)
{
	t_cmd	*cur_cmd;
	int		pid;
	int		ft_pipe[2];

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
	else if (cur_cmd && cur_cmd->argv[0])
	{
		execution_loop(obj, std_in, std_out, env);
		ft_wait_all(obj);
	}
	cleanup_execution(obj, std_in, std_out, env);
	return (130);
}
