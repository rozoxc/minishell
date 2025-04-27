/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/04/27 18:14:40 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_heredoc(t_cmd *cmd)
{
	t_lexer	*lexer;

	lexer = NULL;
	while (cmd)
	{
		lexer = cmd->lexer;
		while (lexer)
		{
			if (lexer->i == HEREDOC)
				return (1);
			lexer = lexer->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

char	*ft_expand(t_obj *obj, char *str)
{
	char	**argv;
	int		i;

	i = 0;
	if (str == NULL || ft_strcmp(str, "") == 0)
		return (ft_strdup(""));
	argv = ft_split(str, ' ');
	free(str);
	str = NULL;
	while (argv[i])
	{
		if (ft_strrchr(argv[i], '$'))
		{
			str = ft_strjoin2(str, get_value(obj, argv[i] + 1), 2);
			free(argv[i]);
		}
		else
			str = ft_strjoin2(str, argv[i], 2);
		i++;
	}
	free(argv);
	return (str);
}

static size_t count_and_prep_dollars(const char **src, size_t *to_copy)
{
	const char *p;
	size_t dollar_count;

	p = *src;
	dollar_count = 0;
	while (*p == '$')
	{
		dollar_count++;
		p++;
	}
	if (*p == '\'')
	{
		if (dollar_count % 2 == 1)
			*to_copy = dollar_count - 1;
		else
			*to_copy = dollar_count;
		return (1);
	}
	return (0);
}

static void copy_content(const char **src, char **dst, const char *p, size_t to_copy)
{
	size_t i;
	
	i = 0;
	while (i < to_copy)
	{
		*(*dst) = '$';
		(*dst)++;
		i++;
	}
	*src = p;
	while (**src != '\'')
		(*src)++;
	(*src)++;
	while (**src && **src != '\'')
	{
		*(*dst) = **src;
		(*dst)++;
		(*src)++;
	}
	if (**src == '\'')
		(*src)++;
}

static size_t handle_dollars(const char **src, char **dst)
{
	const char *p;
	size_t to_copy;

	p = *src;
	if (!count_and_prep_dollars(src, &to_copy))
		return (0);
	
	copy_content(src, dst, p, to_copy);
	return (1);
}

static void	process_characters(const char **src, char **dst)
{
	if (**src != '\'' && **src != '"')
	{
		*(*dst) = **src;
		(*dst)++;
		(*src)++;
	}
	else
		(*src)++;
}

char	*remove_all_quotes(const char *s)
{
	size_t		len;
	char		*out;
	const char	*src;
	char		*dst;

	len = ft_strlen(s);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	src = s;
	dst = out;
	while (*src)
	{
		if (*src == '$')
		{
			if (handle_dollars(&src, &dst))
				continue;
		}
		process_characters(&src, &dst);
	}
	*dst = '\0';
	return (out);
}

static void write_input_line(t_obj *obj, char *str, int fd, char *stop)
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

static void process_input(t_obj *obj, char *s, int fd, char *stop)
{
    char *str;

    while (1)
    {
        str = readline("> ");
        if (str == NULL || ft_strcmp(str, s) == 0)
        {
            free(str);
            close(fd);
            free(s);
            break;
        }
        write_input_line(obj, str, fd, stop);
    }
}

char *ft_run(t_obj *obj, char *stop, int n)
{
    char *file;
    int fd;
    char *s;

    s = remove_all_quotes(stop);
    file = ft_strjoin2(".f", ft_itoa(n), 3);
    fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
    
    process_input(obj, s, fd, stop);
    
    return (file);
}

void	ft_herdoc_execution(t_obj *obj, t_cmd *cmd_t, t_lexer *lexer)
{
	int		i;
	char	*name;

	i = 0;
	while (cmd_t)
	{
		name = NULL;
		lexer = cmd_t->lexer;
		while (lexer)
		{
			if (lexer->i == HEREDOC)
			{
				name = ft_run(obj, lexer->str, i);
				free(lexer->str);
				lexer->str = NULL;
				lexer->str = ft_strdup(name);
				free(name);
				i++;
			}
			lexer = lexer->next;
		}
		cmd_t = cmd_t->next;
	}
}

int	ft_heredoc(t_obj *obj)
{
	t_cmd	*cmd_t;
	t_lexer	*lexer;

	cmd_t = obj->cmd;
	lexer = NULL;
	if (is_heredoc(cmd_t) != 1)
		return (SUCCESS);
	ft_herdoc_execution(obj, cmd_t, lexer);
	return (SUCCESS);
}
