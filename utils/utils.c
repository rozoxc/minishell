/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:39:51 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/31 11:00:53 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_space(char **str)
{
	while (*(*str) == ' ' || *(*str) == '\t' || *(*str) == '\n' \
		|| *(*str) == '\r' || *(*str) == '\v' || *(*str) == '\f')
		(*str)++;
}

char	set_char(char **str, char c)
{
	if (*(*str) == c)
		return (0);
	else
		return (*(*str));
}

int	check_sep(char **str, char c)
{
	if (c != 0)
		return (0);
	else if ((*(*str) == '>' || *(*str) == '<'))
	{
		if (*(*str + 1) == *(*str))
			return (0);
		return (1);
	}
	else if ((ft_is_whitespace(*(*str)) || *(*str) == '|'))
		return (1);
	else if ((ft_is_whitespace(*(*str + 1)) || *(*str + 1) == '|' \
			|| *(*str + 1) == '>' || *(*str + 1) == '<'))
		return (1);
	return (0);
}

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

int	is_only_whitespace(const char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}
