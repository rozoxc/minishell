/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utlis1_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:38:10 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/03 11:40:22 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_single_quote(const char *str, int *i, char *res, int *pos)
{
	int	end;
	int	j;

	end = *i + 1;
	while (str[end] && str[end] != '\'')
		end++;
	if (str[end] == '\'')
	{
		j = *i + 1;
		while (j < end)
			res[(*pos)++] = str[j++];
		*i = end;
	}
	else
		res[(*pos)++] = str[*i];
	return (1);
}

int	handle_double_quote(const char *str, int *i, char *res, int *pos)
{
	int	end;
	int	j;

	end = *i + 1;
	while (str[end] && str[end] != '"')
		end++;
	if (str[end] == '"')
	{
		j = *i + 1;
		while (j < end)
			res[(*pos)++] = str[j++];
		*i = end;
	}
	else
		res[(*pos)++] = str[*i];
	return (1);
}
