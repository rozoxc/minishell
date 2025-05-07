/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:51 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/08 00:25:26 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_red_input(t_lexer *red)
{
	int		fd;

	fd = open(red->str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell Err, infile, No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("Minishell Error: redirection\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	unlink(red->str);
	return (EXIT_SUCCESS);
}

int	set_red_append(t_lexer *red)
{
	int	fd;

	fd = open(red->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell : ambiguous redirect\n", 2);
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
		ft_putstr_fd("minishell : ambiguous redirect\n", 2);
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

	if (cmd == NULL)
		return (0);
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
