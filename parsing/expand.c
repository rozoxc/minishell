/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:19:56 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/20 22:46:27 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	should_split_token(t_token *token)
{
	if (!(ft_strchr(token->str, ' ')))
		return (0);
	if (!token->str)
		return (0);
	return (1);
}

void	create_new_tokens(t_token *token, char **parts)
{
	t_token	*curr;
	t_token	*new_tok;
	int		i;

	curr = token;
	i = 1;
	while (parts[i])
	{
		if (!(ft_strchr(parts[i], ' ')))
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

	if (!should_split_token(token))
		return ;
	parts = ft_split(token->str, ' ');
	if (!parts)
		return ;
	free(token->str);
	token->str = ft_strdup(parts[0]);
	create_new_tokens(token, parts);
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
		fix_norm(token, obj, &j);
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
		if (!ft_strcmp(token->str, "export"))
			obj->split_expand = 1;
		process_token(obj, token, &j, str);
		token = token->next;
	}
}
