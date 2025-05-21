/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/20 23:08:13 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*generate_random_filename(void)
{
	int		fd;
	char	buffer[256];
	char	*file;
	int		i;
	int		j;

	file = malloc(11);
	if (!file)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	read(fd, buffer, sizeof(buffer));
	close(fd);
	i = 0;
	j = 0;
	while ((size_t)i < ft_strlen(buffer) && j < 10)
	{
		if ((buffer[i] >= 97 && buffer[i] <= 122) \
			|| (buffer[i] >= 65 && buffer[i] <= 90))
			file[j++] = buffer[i];
		i++;
	}
	file[j] = '\0';
	return (file);
}

char	*ft_run(t_obj *obj, t_lexer *lexer)
{
	char	*file;
	int		fd;
	char	*s;
	char	*str;
	int		fd2;

	str = handle_dollar_quotes(lexer->str);
	s = remove_all_quotes(str);
	free(str);
	while (1)
	{
		file = generate_random_filename();
		if (file && access(file, F_OK) != 0)
			break ;
		free(file);
	}
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	fd2 = open(file, O_RDONLY);
	open_error(obj, fd, fd2, file);
	process_input(obj, s, fd, lexer->str);
	close(fd2);
	close(fd);
	lexer->fd = fd2;
	return (file);
}

void	ft_process_heredoc(t_obj *obj, t_lexer *lexer)
{
	char	*name;

	if (lexer->i == HEREDOC)
	{
		name = ft_run(obj, lexer);
		free(lexer->str);
		lexer->str = NULL;
		if (!obj->status)
			lexer->str = ft_strdup(name);
		free(name);
	}
}

void	ft_heredoc_execution(t_obj *obj, t_cmd *cmd_t, t_lexer *lexer)
{
	int	i;

	i = 0;
	while (cmd_t && !obj->status)
	{
		lexer = cmd_t->lexer;
		while (lexer && !obj->status)
		{
			if (lexer->i == HEREDOC)
			{
				ft_process_heredoc(obj, lexer);
				i++;
			}
			lexer = lexer->next;
		}
		if (obj->status)
			break ;
		cmd_t = cmd_t->next;
	}
}

int	ft_heredoc(t_obj *obj)
{
	t_cmd		*cmd_t;
	t_lexer		*lexer;

	obj->status = 0;
	cmd_t = obj->cmd;
	lexer = NULL;
	if (is_heredoc(cmd_t) != 1)
		return (SUCCESS);
	ft_heredoc_execution(obj, cmd_t, lexer);
	if (obj->status)
		return (FAILURE);
	return (SUCCESS);
}
