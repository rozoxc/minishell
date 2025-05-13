/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:41:15 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/13 14:05:44 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*no_quotes(t_obj *obj, char **argv, int *i, int *j)
{
	char	*str;
	int		x;

	x = 0;
	str = NULL;
	(void)j;
	while (argv[*i] && ft_strcmp(argv[*i], "\"") && ft_strcmp(argv[*i], "\'"))
	{
		if (ft_strchr(argv[*i], '$'))
		{
			if (ft_strchr(argv[*i], '='))
				x++;
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
			if (x > 0)
				str = ft_strjoin2(str, "=", 1);
			x = 0;
		}
		else
			str = ft_strjoin2(str, argv[*i], 1);
		(*i)++;
	}
	return (str);
}

char	*do_quotes(t_obj *obj, char **argv, int *i, int *j)
{
	char	*str;
	char	*s;

	str = NULL;
	(void)j;
	while (argv[*i])
	{
		if (ft_strchr(argv[*i], '$'))
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
		else
			str = ft_strjoin2(str, argv[*i], 1);
		(*i)++;
	}
	s = remove_all_quotes(str);
	free(str);
	return (s);
}

char	*si_quotes(t_obj *obj, char **argv, int *i)
{
	char	*str;
	char	*s;
	int		count = 0;

	while (argv[count] && ft_strchr(argv[count], '\''))
			count++;
	str = NULL;
	while (argv[*i])
	{
		if (count % 2 == 0 && ft_strchr(argv[*i], '$'))
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
		else
			str = ft_strjoin2(str, argv[*i], 1);
		(*i)++;
	}
	s = remove_all_quotes(str);
	free(str);
	return (s);
}

t_token	*create_token(char *str)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = str;
	tok->next = NULL;
	return (tok);
}

char	*get_special_value(t_obj *obj, char *str)
{
	char	*value;

	value = NULL;
	if (*str == '\0')
		value = ft_strdup("$");
	else if (*str == '%')
		value = ft_strdup("$%");
	else if (*str == '?')
		value = ft_strjoin2(value, ft_itoa(obj->exit_code), 3);
	else if (*str == '.')
		value = ft_strdup("$.");
	return (value);
}
