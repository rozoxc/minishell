/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:36 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/16 19:17:10 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(int fd1, int fd2)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}

int	count_cmds(t_obj *obj)
{
	t_cmd	*cmd_temp;
	int		count;

	count = 0;
	cmd_temp = obj->cmd;
	while (cmd_temp)
	{
		count++;
		cmd_temp = cmd_temp->next;
	}
	return (count);
}

int	ft_process_wait_status(pid_t pid, int status, t_obj *obj)
{
	if (pid == -1)
		obj->exit_code = 1;
	else
	{
		if (WIFEXITED(status))
			obj->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			obj->exit_code = 128 + WTERMSIG(status);
		else
			obj->exit_code = 1;
	}
	return (obj->exit_code);
}

void	ft_wait_all(t_obj *obj)
{
	int		status;
	int		i;
	int		cmd_count;
	pid_t	pid;

	i = 0;
	cmd_count = count_cmds(obj);
	while (i < cmd_count)
	{
		pid = waitpid(obj->pid[i], &status, 0);
		ft_process_wait_status(pid, status, obj);
		i++;
	}
	obj->flag = 0;
	free(obj->pid);
}

void	shift_empty_args(char *argv[])
{
	int	skip;
	int	i;

	skip = 0;
	while (argv[skip] != NULL && argv[skip][0] == '\0')
	{
		free(argv[skip]);
		skip++;
	}
	if (skip > 0)
	{
		i = 0;
		while (argv[skip + i] != NULL)
		{
			argv[i] = argv[skip + i];
			i++;
		}
		argv[i] = NULL;
	}
}
