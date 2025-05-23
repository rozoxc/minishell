/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:53:42 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/24 15:35:46 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shift_env_arg(char *argv[])
{
	int	i;

	i = 0;
	free(argv[0]);
	while (argv[i + 1] != NULL)
	{
		argv[i] = argv[i + 1];
		i++;
	}
	argv[i] = NULL;
}

void	shift_empty_args_cmds(t_cmd *cmd)
{
	char	**av;
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		av = current->argv;
		if (av != NULL)
		{
			if (av[0] != NULL && ft_strcmp(av[0], "env") == 0 \
				&& (av[1] != NULL && av[1][0] != '\0'))
				shift_env_arg(av);
			shift_empty_args(av);
		}
		current = current->next;
	}
}

void	child_process_execution(t_obj *obj, char *path, \
		t_cmd *cur_cmd, char **env)
{
	if (obj->cmd && obj->cmd->argv[0] == NULL && (ft_strchr(obj->str, '"') \
		|| ft_strchr(obj->str, '\'')))
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		exit(determine_exit_code(obj, 127));
	}
	if (is_only_whitespace(cur_cmd->argv[0]))
	{
		cur_cmd = cur_cmd->next;
		exit(determine_exit_code(obj, 0));
	}
	path = get_command_path(obj, cur_cmd->argv[0]);
	if (execve(path, cur_cmd->argv, env) == -1)
		handle_execution_error(obj, path, env);
}

char	*get_command_path(t_obj *obj, char *cmd)
{
	char	*path;

	if (cmd[0] == '.' && cmd[1] == '/')
		path = ft_strdup(cmd);
	else if (ft_strchr(&cmd[0], '/'))
		path = ft_strdup(cmd);
	else
	{
		path = get_path(obj, cmd);
		if (path == NULL)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			exit(determine_exit_code(obj, 127));
		}
	}
	return (path);
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
