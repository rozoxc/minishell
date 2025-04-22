/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:19:56 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/22 10:54:04 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ' || str[i] == '?')
			return (-1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (i);
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
	else if (*str == '?')
		value = ft_strjoin2(value, ft_itoa(obj->exit_code), 3);
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

char	*no_quotes(t_obj *obj, char **argv, int *i)
{
	char	*str;

	str = NULL;
	while (argv[*i] && ft_strcmp(argv[*i], "\"") && ft_strcmp(argv[*i], "\'"))
	{
		if (ft_strchr(argv[*i], '$'))
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
		else
			str = ft_strjoin2(str, argv[*i], 1);
		(*i)++;
	}
	return (str);
}

char	*do_quotes(t_obj *obj, char **argv, int *i)
{
	char	*str;

	str = NULL;
	(*i)++;
	while (argv[*i] && ft_strcmp(argv[*i], "\""))
	{
		if (ft_strchr(argv[*i], '$'))
			str = ft_strjoin2(str, get_value(obj, argv[*i] + 1), 2);
		else
			str = ft_strjoin2(str, argv[*i], 1);
		(*i)++;
	}
	(*i)++;
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
	(*i)++;
	return (str);
}

void expand(t_obj *obj)
{
    t_token *token;
    char **argv;
    int i;

    token = obj->token;
    while (token)
    {
        if (token->str && ft_strcmp(token->str, "<<") == 0)
        {
            token = token->next;
            if (token)
                token = token->next;
            continue;
		}
        i = 0;
        argv = ft_split(token->str, ' ');
        free(token->str);
        token->str = NULL;
        while (argv[i])
        {
            if (ft_strcmp(argv[i], "\'") == 0)
                token->str = ft_strjoin2(token->str, si_quotes(argv, &i), 2);
            else if (ft_strcmp(argv[i], "\"") == 0)
                token->str = ft_strjoin2(token->str, \
                do_quotes(obj, argv, &i), 2);
            else
                token->str = ft_strjoin2(token->str, \
                no_quotes(obj, argv, &i), 2);
        }
        free_argv(argv);
        token = token->next;
    }
}
