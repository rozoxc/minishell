/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:21:41 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/20 22:52:50 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_error(t_obj *obj, int fd1, int fd2, char *file)
{
	unlink(file);
	if (fd1 == -1 || fd2 == -1)
	{
		ft_putstr_fd("file to open the file\n", 2);
		if (fd1 != -1)
			close(fd1);
		if (fd2 != -1)
			close (fd2);
		exit(determine_exit_code(obj, 1));
	}
}

void	exit_code_pipe(t_obj *obj, t_token *token)
{
	obj->exit_code = 0;
	token->type = PIPE;
}

void	count_heredoc(t_obj *obj, t_token *token)
{
	token->type = HEREDOC;
	obj->count_heredoc++;
	if (obj->count_heredoc >= 17)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
}

void	fix_norm(t_token *token, t_obj *obj, int *j)
{
	if (token->type == COMMAND)
	{
		obj->split_expand = 0;
		*j = 0;
	}
	if (token->type == COMMAND && ft_strchr(token->str, '$'))
		*j = 1;
}

void	export_equal(char **av, int *j, int *count)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_strchr(av[i], '='))
		{
			i++;
			while (av[i] && ft_strchr(av[i], '\''))
			{
				i++;
				(*count)++;
			}
			return ;
		}
		if (av[i][0] == '\'')
		{
			(*j)++;
			if ((*count) % 2 != 0)
				(*count)++;
			return ;
		}
		i++;
	}
	return ;
}
