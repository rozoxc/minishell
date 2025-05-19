/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:27:03 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/19 10:40:30 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_no_file_error(t_obj *obj, char *path)
{
	ft_putstr_fd("minishell: No such file or directory\n", 2);
	free(path);
	exit(determine_exit_code(obj, 127));
}

void	handle_enoexec_error(t_obj *obj, char *path, char **env)
{
	struct stat	fs;
	char		*sh_args[3];

	if (stat(path, &fs) == 0)
	{
		sh_args[0] = "/bin/sh";
		sh_args[1] = path;
		sh_args[2] = NULL;
		execve("/bin/sh", sh_args, env);
		ft_putstr_fd("minishell: Is a directory\n", 2);
	}
	else
		ft_putstr_fd("minishell: Permission denied\n", 2);
	free(path);
	exit(determine_exit_code(obj, 126));
}

void	handle_other_exec_errors(t_obj *obj, char *path)
{
	struct stat	fs;

	if (stat(path, &fs) == 0 && S_ISDIR(fs.st_mode))
	{
		if (ft_strchr(obj->cmd->argv[0], '/'))
			ft_putstr_fd("minishell: Is a directory\n", 2);
		else
		{
			ft_putstr_fd("minishell: command not fond\n", 2);
			exit(determine_exit_code(obj, 127));
		}
	}
	else
		ft_putstr_fd("minishell: Permission denied\n", 2);
	free(path);
	exit(determine_exit_code(obj, 126));
}

void	handle_exec_format_error(t_obj *obj, char *path, char **env)
{
	if (errno == ENOEXEC)
		handle_enoexec_error(obj, path, env);
	else
		handle_other_exec_errors(obj, path);
}

void	handle_execution_error(t_obj *obj, char *path, char **env)
{
	if (errno == ENOENT)
		handle_no_file_error(obj, path);
	else
		handle_exec_format_error(obj, path, env);
}
