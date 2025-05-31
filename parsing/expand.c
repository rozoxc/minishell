/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:19:56 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/31 14:53:56 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_new_tokens(t_token *token, char **parts, int i)
{
	t_token	*curr;
	t_token	*new_tok;

	curr = token;
	i++;
	while (parts[i])
	{
		if (!(ft_strchr(parts[i], ' ')) && !(ft_strchr(parts[i], '\t')))
		{
			new_tok = create_token(ft_strdup(parts[i]));
			new_tok->next = curr->next;
			curr->next = new_tok;
			curr = new_tok;
		}
		i++;
	}
}

void	split_expanded(t_token *token)
{
	char	**parts;
	int		i;
	int		count;

	if (!contains_whitespace(token->str))
		return ;
	count = ft_count_words(token->str);
	parts = ft_split_export(token->str, ' ');
	if (!parts)
		return ;
	i = 0;
	while (is_all_whitespace(parts[i]))
		i++;
	if (count > 1)
	{
		free(token->str);
		token->str = ft_strdup(parts[i]);
		create_new_tokens(token, parts, i);
	}
	else
	{
		free(token->str);
		token->str = ft_strdup(parts[i]);
	}
	free_argv(parts);
}

char	*get_value(t_obj *obj, char *str)
{
	char	*value;

	value = handle_special_chars(obj, str);
	if (value == NULL)
		value = lookup_env_value(obj, str);
	if (value == NULL)
		value = ft_strdup("");
	return (value);
}

void	expand(t_obj *obj)
{
	t_token	*token;
	char	*str;
	int		j;

	j = 1;
	token = obj->token;
	while (token)
	{
		check_type(token, obj, &j);
		if (token->str && ft_strcmp(token->str, "<<") == 0)
		{
			handle_special_tokens(&token);
			continue ;
		}
		str = remove_all_quotes(token->str);
		if ((!ft_strcmp(str, "export") && (token->prev != NULL)) \
		|| (!ft_strcmp(str, "export") && (ft_strchr(token->str, '\'') \
		|| ft_strchr(token->str, '"'))))
			j = 1;
		if (!ft_strcmp(str, "export"))
			obj->split_expand = 1;
		process_token(obj, token, &j, str);
		token = token->next;
	}
}
