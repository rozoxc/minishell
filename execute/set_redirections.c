/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:51 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/31 14:22:32 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_red_input(t_lexer *red)
{
	int	fd;

	if (red->i == INPUT)
	{
		fd = open(red->str, O_RDONLY);
		if (fd < 0)
			return (ft_putstr_fd("minishell: No such \
file or directory\n", 2), EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			ft_putstr_fd("Minishell Error: redirection\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		close(fd);
	}
	else
	{
		if (dup2(red->fd, STDIN_FILENO) < 0)
		{
			ft_putstr_fd("Minishell Error: redirection\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		close(red->fd);
	}
	return (EXIT_SUCCESS);
}

int	set_red_append(t_lexer *red)
{
	int	fd;

	fd = open(red->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: error to open the file\n", 2);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("Minishell Err: redirection\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

int	set_red_trunc(t_lexer *red)
{
	int	fd;

	fd = open(red->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: error to open the file\n", 2);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("Minishell Err: redirection\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close (fd);
	return (EXIT_SUCCESS);
}

int	set_redirections(t_cmd *cmd)
{
	t_lexer	*red_temp;

	red_temp = cmd->lexer;
	while (red_temp)
	{
		if (red_temp->i == INPUT || red_temp->i == HEREDOC)
		{
			if (set_red_input(red_temp) == EXIT_FAILURE)
				return (Q_ERROR);
		}
		else if (red_temp->i == TRUNC)
		{
			if (set_red_trunc(red_temp) == EXIT_FAILURE)
				return (Q_ERROR);
		}
		else if (red_temp->i == APPEND)
		{
			if (set_red_append(red_temp) == EXIT_FAILURE)
				return (Q_ERROR);
		}
		red_temp = red_temp->next;
	}
	return (0);
}

void	clear_heredoc_lexers(t_obj *obj)
{
	t_lexer	*current;
	t_lexer	*next;

	current = obj->cmd->lexer;
	while (current)
	{
		next = current->next;
		if (current->i == HEREDOC)
			close(current->fd);
		free(current->str);
		free(current);
		current = next;
	}
	obj->cmd->lexer = NULL;
}
