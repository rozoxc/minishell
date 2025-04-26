/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:42:47 by hfalati           #+#    #+#             */
/*   Updated: 2025/04/26 16:33:48 by hfalati          ###   ########.fr       */
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

#include <stdlib.h>

size_t  ft_strlen(const char *s);  /* your libft strlen */

char    *remove_all_quotes(const char *s)
{
    size_t  len;
    char    *out;
    const char *src;
    char    *dst;

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
            const char  *p = src;
            size_t      dollar_count = 0;
            size_t      to_copy;
            size_t      i;

            while (*p == '$')
            {
                dollar_count++;
                p++;
            }
            if (*p == '\'')
            {
                if (dollar_count % 2 == 1)
                    to_copy = dollar_count - 1;
                else
                    to_copy = dollar_count;
                i = 0;
                while (i < to_copy)
                {
                    *dst = '$';
                    dst++;
                    i++;
                }
                src = p + 1;
                while (*src && *src != '\'')
                {
                    *dst = *src;
                    dst++;
                    src++;
                }
                if (*src == '\'')
                    src++;
                continue;
            }
        }
        if (*src != '\'' && *src != '"')
        {
            *dst = *src;
            dst++;
            src++;
        }
        else
            src++;
    }
    *dst = '\0';
    return (out);
}


char	*ft_run(t_obj *obj, char *stop, int n)
{
	char	*str;
	char	*file;
	int		fd;
	char	*s;

	s = remove_all_quotes(stop);
	file = ft_strjoin2(".f", ft_itoa(n), 3);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		str = readline("> ");
		if (str == NULL || ft_strcmp(str, s) == 0)
		{
			free(str);
			close(fd);
			free(s);
			break ;
		}
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
