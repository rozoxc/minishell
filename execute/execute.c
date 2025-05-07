/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:20 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/07 16:28:26 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_command_path(t_obj *obj, char *cmd)
{
	char *path;

	if (cmd[0] == '.' && cmd[1] == '/')
		path = ft_strdup(cmd);
	else if (cmd[0] == '/')
		path = ft_strdup(cmd);
	else
	{
		path = get_path(obj, cmd);
		if (path == NULL)
		{
			perror("command not found");
			exit(determine_exit_code(obj, 127));
		}
	}
	if (cmd[0] == '\0')
		exit(determine_exit_code(obj, 0));
	return (path);
}

void handle_no_file_error(t_obj *obj, char *cmd_name, char *path)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd_name, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    free(path);
    exit(determine_exit_code(obj, 127));
}

void	handle_exec_format_error(t_obj *obj, char *cmd_name, char *path, char **env)
{
	struct stat	fs;
	char		*sh_args[3];

	if (errno == ENOEXEC)
	{
		if (stat(cmd_name, &fs) == 0)
		{
			sh_args[0] = "/bin/sh";
			sh_args[1] = path;
			sh_args[2] = NULL;
			execve("/bin/sh", sh_args, env);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putstr_fd(": Is a directory\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
	}
	else
		perror("minishell: ");
	free(path);
	exit(determine_exit_code(obj, 126));
}


void handle_execution_error(t_obj *obj, char *cmd_name, char *path, char **env)
{
    if (errno == ENOENT)
        handle_no_file_error(obj, cmd_name, path);
    else
        handle_exec_format_error(obj, cmd_name, path, env);
}

void child_process_execution(t_obj *obj, char *path, t_cmd *cur_cmd, char **env)
{
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

	env = env_to_array(obj->env);
	std_in = dup_error(obj, dup(STDIN_FILENO));
	std_out = dup_error(obj, dup(STDOUT_FILENO));
	cur_cmd = obj->cmd;
	if (ft_heredoc(obj) == FAILURE)
		return (1);
	if (cur_cmd && cur_cmd->argv[0] && check_build(cur_cmd->argv[0]) && \
		cur_cmd->next == NULL)
	{
		if (set_redirections(cur_cmd) == Q_ERROR)
			return (determine_exit_code(obj, 1), 1);
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
