/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:00:21 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/05 09:01:18 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **str, int i)
{
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free (str);
	return (0);
}

static int	ft_count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_putword(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_words(char const *s, char c, char **str, int num_words)
{
	int	i;
	int	word;
	int	words_len;

	i = 0;
	word = 0;
	words_len = 0;
	while (word < num_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			words_len++;
		}
		str[word] = (char *)malloc(sizeof(char) * (words_len + 1));
		if (!str[word])
			return (free_array(str, word));
		ft_putword (str[word], s, i, words_len);
		words_len = 0;
		word++;
	}
	str[word] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	unsigned int	num_words;

	if (!s)
		return (0);
	num_words = ft_count_words(s, c);
	str = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!str)
		return (0);
	str = ft_split_words(s, c, str, num_words);
	return (str);
}
