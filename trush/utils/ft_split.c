/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozox <rozox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 04:45:49 by rozox             #+#    #+#             */
/*   Updated: 2025/03/21 05:12:24 by rozox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_word(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if ((str[i + 1] == c && str[i] != c)
			|| (str[i] != c && str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_lenght(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			break ;
		}
		i++;
	}
	return (i);
}

static char	*return_words(char *str, char c)
{
	int		i;
	int		x;
	char	*p;

	i = 0;
	x = ft_lenght(str, c);
	p = malloc(sizeof(char) * (x + 1));
	if (!p)
		return (NULL);
	while (i < x)
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char	*my_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		size;
	char	**p;

	if (!s)
		return (NULL);
	size = count_word((char *)s, c);
	p = (char **)malloc(sizeof(char *) * (size + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < size)
	{
		while (*s == c)
			s++;
		p[i] = return_words((char *)s, c);
		if (p[i] == NULL)
		{
			my_free(p);
		}
		s += ft_lenght((char *)s, c);
		i++;
	}
	p[i] = NULL;
	return (p);
}