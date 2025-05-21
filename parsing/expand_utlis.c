/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:41:15 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/21 15:42:38 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*no_quotes(t_obj *obj, char **argv, int *i, int *j)
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

void	scan_until_equal(char **av, int *j)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_strchr(av[i], '='))
			return ;
		if (av[i][0] == '"')
		{
			(*j)++;
			return ;
		}
		i++;
	}
	return ;
}

char	*do_quotes(t_obj *obj, char **argv, int *i, int *j)
{
	char	*str;
	char	*s;

	str = NULL;
	if (obj->split_expand == 1)
		scan_until_equal(argv, j);
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
	if (obj->split_expand == 1)
		export_equal(argv, j, &count);
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
