/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/13 15:47:57 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_input(t_obj *obj, char *s, int fd, char *stop)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		process_child(obj, s, fd, stop);
	else
	{
		free(s);
		waitpid(pid, &status, 0);
		signal(SIGINT, SIG_DFL);
		if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
			obj->status = 1;
	}
}

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
		if (buffer[i] >= 32 && buffer[i] <= 126)
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
		if (ft_strchr(file, '/'))
			continue ;
		else if (!file || access(file, F_OK) != 0)
			break ;
		free(file);
	}
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		printf("!!!!-->%s\n", file);
	fd2 = open(file, O_RDONLY);
	unlink(file);
	process_input(obj, s, fd, lexer->str);
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
