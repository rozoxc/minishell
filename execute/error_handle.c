/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:30 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/14 12:01:20 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	determine_exit_code(t_obj *obj, int exit_code)
{
	obj->exit_code = exit_code;
	return (exit_code);
}

void	pipe_error(t_obj *obj, int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell error : fail to create pipe\n", 2);
		exit(determine_exit_code(obj, 1));
	}
}

int	fork_error(t_obj *obj, int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		determine_exit_code(obj, 1);
	}
	return (pid);
}

int	dup_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: fail to dup\n", 2);
		exit(determine_exit_code(obj, 1));
	}
	return (dup);
}

void	dup2_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: fail to dup2\n", 2);
		exit(determine_exit_code(obj, 1));
	}
}
