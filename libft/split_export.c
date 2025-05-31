/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:11:53 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/31 15:13:39 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	count_parts(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (is_whitespace(*s))
		{
			while (*s && is_whitespace(*s))
				s++;
			count++;
		}
		else
		{
			while (*s && !is_whitespace(*s))
				s++;
			count++;
		}
	}
	return (count);
}

char	*substr(const char *start, const char *end)
{
	size_t	len;
	char	*res;

	len = end - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, start, len);
	res[len] = '\0';
	return (res);
}

int	ft_fill_split_export(char **result, const char *s)
{
	int			i;
	const char	*start;

	i = 0;
	while (*s)
	{
		if (is_whitespace(*s))
		{
			start = s;
			while (*s && is_whitespace(*s))
				s++;
			result[i++] = ft_strdup(" ");
		}
		else
		{
			start = s;
			while (*s && !is_whitespace(*s))
				s++;
			result[i++] = substr(start, s);
		}
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split_export(const char *s, char c)
{
	char	**result;
	int		count;

	(void)c;
	if (!s)
		return (NULL);
	count = count_parts(s);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	ft_fill_split_export(result, s);
	return (result);
}
