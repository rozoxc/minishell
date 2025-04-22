/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:56:04 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/22 09:56:15 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_free_if_error(char **array, size_t i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
	return (NULL);
}

static int	ft_word_len(const char *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && !(*(str + i) == charset))
		i++;
	return (i);
}

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	w;

	w = 0;
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		i = ft_word_len(str, c);
		str += i;
		if (i)
			w++;
	}
	return (w);
}

static char	*ft_create_word_copy(const char *src, size_t n)
{
	char	*dest;

	dest = malloc((n + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	ft_strlcpy(dest, src, n + 1);
	return (dest);
}

char	**ft_split_simple(char const *str, char charset)
{
	char	**array;
	int		size;
	int		i;
	int		n;
	char	*temp_word;

	size = ft_count_words(str, charset);
	array = malloc ((size + 1) * sizeof(char *));
	if (!(array))
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*str && (*str == charset))
			str++;
		n = ft_word_len(str, charset);
		temp_word = ft_create_word_copy(str, n);
		array[i] = temp_word;
		if (!array[i])
			return (ft_free_if_error(array, i));
		str += n;
	}
	array[size] = 0;
	return (array);
}

char **env_to_array(t_env *env)
{
    t_env *current;
    char **array;
    int count;
    int i;

    count = 0;
    current = env;
    while (current)
    {
        count++;
        current = current->next;
    }
    array = (char **)malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);
    i = 0;
    current = env;
    while (current)
    {
        array[i] = ft_strdup(current->value);
        if (!array[i])
        {
            while (--i >= 0)
                free(array[i]);
            free(array);
            return (NULL);
        }
        current = current->next;
        i++;
    }
    array[count] = NULL;
    return (array);
}
