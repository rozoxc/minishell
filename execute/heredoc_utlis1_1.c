/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utlis1_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:38:10 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/14 16:33:11 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_single_quote(const char *str, int *i, char *res, int *pos)
{
	int	end;
	int	j;

	end = *i + 1;
	while (str[end] && str[end] != '\'')
		end++;
	if (str[end] == '\'')
	{
		j = *i + 1;
		while (j < end)
			res[(*pos)++] = str[j++];
		*i = end;
	}
	else
		res[(*pos)++] = str[*i];
	return (1);
}

int	handle_double_quote(const char *str, int *i, char *res, int *pos)
{
	int	end;
	int	j;

	end = *i + 1;
	while (str[end] && str[end] != '"')
		end++;
	if (str[end] == '"')
	{
		j = *i + 1;
		while (j < end)
			res[(*pos)++] = str[j++];
		*i = end;
	}
	else
		res[(*pos)++] = str[*i];
	return (1);
}

void	write_input_line(t_obj *obj, char *str, int fd, char *stop)
{
	if (ft_strchr(stop, '\'') || ft_strchr(stop, '"'))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	else
	{
		str = ft_expand(obj, str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
}

void	process_child(t_obj *obj, char *s, int fd, char *stop)
{
	char	*str;

	signal(SIGINT, heredoc_signal);
	while (1)
	{
		str = readline("> ");
		if (str == NULL || ft_strcmp(str, s) == 0)
		{
			close(fd);
			free(s);
			exit(0);
		}
		write_input_line(obj, str, fd, stop);
	}
}
