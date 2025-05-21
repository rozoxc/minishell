/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:20 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/21 01:10:20 by hfalati          ###   ########.fr       */
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

void	execution_loop(t_obj *obj, int fd_in, int fd_out, char **env)
{
	t_cmd	*cur_cmd;
	int		pid;
	int		ft_pipe[2];
	t_lexer	*lexer;
	int	fd;

	cur_cmd = obj->cmd;
	pid = 0;
	signal(SIGINT, SIG_IGN);
	obj->pid = malloc(sizeof(t_cmd) * count_cmds(obj));
	while (cur_cmd && cur_cmd->argv[0])
	{
		pipe_error(obj, pipe(ft_pipe));
		obj->pid[pid] = fork_error(obj, fork());
		if (obj->pid[pid] == -1)
			break ;
		if (obj->pid[pid] == 0)
		{
			close(fd_in);
			close(fd_out);
			obj->flag = 1;
			child_process(obj, cur_cmd, ft_pipe, env);
		}
		else
			handle_parent(obj, &cur_cmd, &pid, ft_pipe);
	}
	while (cur_cmd && !cur_cmd->argv[0])
	{
		lexer = cur_cmd->lexer;
		while (lexer)
		{
			if (lexer->i != HEREDOC)
			{
				if (lexer->str[0] == '\0')
				{
					ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				}
				fd = open(lexer->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
				close(fd);
			}
			lexer = lexer->next;
		}
		cur_cmd = cur_cmd->next;
	}
}

int	setup_execution(t_obj *obj, int *std_in, int *std_out, char ***env)
{
	t_obj *tmp_obj = obj;
	*env = env_to_array(tmp_obj->env);
	*std_in = dup_error(tmp_obj, dup(STDIN_FILENO));
	*std_out = dup_error(tmp_obj, dup(STDOUT_FILENO));
	if (ft_heredoc(tmp_obj) == FAILURE)
	{
		while (tmp_obj->cmd->lexer)
		{
			if (tmp_obj->cmd->lexer->i == HEREDOC)
			{
				free(tmp_obj->cmd->lexer->str);
				free(tmp_obj->cmd->lexer);
				close(tmp_obj->cmd->lexer->fd);
			}
			else
			{
				free(tmp_obj->cmd->lexer->str);
				free(tmp_obj->cmd->lexer);
			}
			tmp_obj->cmd->lexer = tmp_obj->cmd->lexer->next;
		}
		cleanup_execution(tmp_obj, *std_in, *std_out, *env);
		return (determine_exit_code(obj, 1), 1);
	}
	return (0);
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
