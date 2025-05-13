/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:17:22 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/13 21:22:32 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

int	ft_skip(const char **str)
{
	if (**str != '\0')
	{
		(*str)++;
		return (1);
	}
	return (0);
}

int	ft_sep2(char c)
{
	return (c == '$' || c == '\'' || c == '\"');
}

int	dollar_len(const char **str)
{
	if ((*str)[0] == '$' && (*str)[1] == '$')
	{
		*str += 2;
		return (2);
	}
	return (0);
}

void	free_split(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
