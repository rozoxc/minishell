/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:41:15 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/18 14:09:33 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*no_quotes(t_obj *obj, char **argv, int *i, int *j)
{
	char	*str;

	str = NULL;
	while (argv[*i] && ft_strcmp(argv[*i], "\"") && ft_strcmp(argv[*i], "\'"))
	{
		if (ft_strchr(argv[*i], '$'))
		{
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
			(*j)++;
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
	while (argv[*i])
	{
		if (ft_strchr(argv[*i], '$'))
		{
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
			(*j)++;
		}
		else
			str = ft_strjoin2(str, argv[*i], 1);
		(*i)++;
	}
	s = remove_all_quotes(str);
	free(str);
	return (s);
}

char	*si_quotes(t_obj *obj, char **argv, int *i, int *j)
{
	char	*str;
	char	*s;
	int		count;

	count = 0;
	while (argv[count] && ft_strchr(argv[count], '\''))
		count++;
	str = NULL;
	while (argv[*i])
	{
		if (count % 2 == 0 && ft_strchr(argv[*i], '$'))
		{
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
			(*j)++;
		}
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
