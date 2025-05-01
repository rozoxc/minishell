/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:19:56 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/01 13:33:55 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *create_token(char *str)
{
    t_token *tok = malloc(sizeof(t_token));
    if (!tok) return NULL;
    tok->str = str;
    tok->next = NULL;
    return tok;
}

void split_expanded(t_token *token)
{
	int i;
	if (ft_strchr(token->str, '='))
		return ;
	if (!(ft_strchr(token->str, ' ')))
		return ;
    if (!token->str)
        return;
    char **parts = ft_split(token->str, ' ');
    if (!parts)
		return;
    free(token->str);
     token->str = ft_strdup(parts[0]);
    t_token *curr = token;
	i = 1;
	while (parts[i])
    {
		if (!(ft_strchr(parts[i], ' ')))
		{
			t_token *new_tok = create_token(ft_strdup(parts[i]));
    	    new_tok->next = curr->next;
        	curr->next = new_tok;
        	curr = new_tok;
		}
		i++;
	}
    free_argv(parts);
}

char	*get_value(t_obj *obj, char *str)
{
	char	*value;
	int		equal;
	t_env	*env;

	equal = 0;
	env = obj->env;
	value = NULL;
	if (*str == '\0')
		value = ft_strdup("$");
	else if (*str == '%')
		value = ft_strdup("$%");
	else if (*str == '?')
		value = ft_strjoin2(value, ft_itoa(obj->exit_code), 3);
	else if (*str == '.')
		value = ft_strdup("$.");
	while (env && value == NULL)
	{
		equal = check_equal(env->value);
		if ((ft_strncmp(str, env->value, ft_strlen(str)) == 0 \
			&& ft_strncmp(env->value, str, equal) == 0))
			value = ft_strdup(ft_strchr(env->value, '=') + 1);
		env = env->next;
	}
	if (value == NULL)
		value = ft_strdup("");
	return (value);
}

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

	str = NULL;
	(*i)++;
	while (argv[*i] && ft_strcmp(argv[*i], "\""))
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

char	*si_quotes(char **argv, int *i)
{
	char	*str;

	str = NULL;
	(*i)++;
	while (argv[*i] && ft_strcmp(argv[*i], "\'"))
	{
		str = ft_strjoin2(str, argv[*i], 1);
		(*i)++;
	}
	return (str);
}

void	expand(t_obj *obj)
{
	t_token	*token;
	char	**argv;
	int	i;
	int j;

	j = 0;
	token = obj->token;
	while (token)
	{
		if (token->str && ft_strcmp(token->str, "<<") == 0)
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		i = 0;
		argv = ft_split(token->str, ' ');
		free(token->str);
		token->str = NULL;
		while (argv[i])
		{
			if (argv[i][0] == '$' && argv[i][1] == '\0' && argv[i+1] && !ft_strcmp(argv[i+1], "\'"))
			{
				i++;
				i++;
				while (argv[i] && ft_strcmp(argv[i], "\'"))
				{
					token->str = ft_strjoin2(token->str, argv[i], 1);
					i++;
				}
				if (argv[i] && !ft_strcmp(argv[i], "\'"))
					i++;
			}
			else if (ft_strcmp(argv[i], "\'") == 0)
				token->str = ft_strjoin2(token->str, si_quotes(argv, &i), 2);
			else if (ft_strcmp(argv[i], "\"") == 0)
				token->str = ft_strjoin2(token->str, \
						do_quotes(obj, argv, &i, &j), 2);
			else
				token->str = ft_strjoin2(token->str, \
						no_quotes(obj, argv, &i, &j), 2);
		}
		if (j == 1)
			split_expanded(token);
		free_argv(argv);
		token = token->next;
	}
}
