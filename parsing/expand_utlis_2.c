/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utlis_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:20:22 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/10 14:10:25 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_quotes(t_obj *obj, t_token *token, char **argv, int *ij)
{
	int	*i;
	int	*j;

	i = &ij[0];
	j = &ij[1];
	if (argv[*i][0] == '$' && argv[*i][1] == '\0' && argv[*i + 1]
			&& !ft_strcmp(argv[*i + 1], "\'"))
	{
		(*i)++;
		(*i)++;
		while (argv[*i] && ft_strcmp(argv[*i], "\'"))
		{
			token->str = ft_strjoin2(token->str, argv[*i], 1);
			(*i)++;
		}
		if (argv[*i] && !ft_strcmp(argv[*i], "\'"))
			(*i)++;
	}
	else if (ft_strcmp(argv[*i], "\'") == 0)
		token->str = ft_strjoin2(token->str, si_quotes(argv, i), 2);
	else if (ft_strcmp(argv[*i], "\"") == 0)
		token->str = ft_strjoin2(token->str, do_quotes(obj, argv, i, j), 2);
	else
		token->str = ft_strjoin2(token->str, no_quotes(obj, argv, i, j), 2);
}

void	process_token(t_obj *obj, t_token *token, int *j)
{
	int		ij[2];
	char	**argv;

	argv = ft_split(token->str, ' ');
	free(token->str);
	token->str = NULL;
	ij[0] = 0;
	ij[1] = *j;
	while (argv[ij[0]])
		process_quotes(obj, token, argv, ij);
	*j = ij[1];
	if (*j == 1)
		split_expanded(token);
	free_argv(argv);
}

void	handle_special_tokens(t_token **token_ptr)
{
	t_token	*token;

	token = *token_ptr;
	if (token->str && ft_strcmp(token->str, "<<") == 0)
	{
		*token_ptr = token->next;
		if (*token_ptr)
			*token_ptr = (*token_ptr)->next;
	}
	else
		*token_ptr = token->next;
}
