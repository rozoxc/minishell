/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:45:03 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/02 10:38:15 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_content(const char **src, char **dst, \
	const char *p, size_t to_copy)
{
	size_t	i;

	i = 0;
	while (i < to_copy)
	{
		*(*dst) = '$';
		(*dst)++;
		i++;
	}
	*src = p;
	while (**src != '\'')
		(*src)++;
	(*src)++;
	while (**src && **src != '\'')
	{
		*(*dst) = **src;
		(*dst)++;
		(*src)++;
	}
	if (**src == '\'')
		(*src)++;
}

size_t	handle_dollars(const char **src, char **dst)
{
	const char	*p;
	size_t		to_copy;

	p = *src;
	if (!count_and_prep_dollars(src, &to_copy))
		return (0);
	copy_content(src, dst, p, to_copy);
	return (1);
}

void	process_characters(const char **src, char **dst)
{
	if (**src != '\'' && **src != '"')
	{
		*(*dst) = **src;
		(*dst)++;
		(*src)++;
	}
	else
		(*src)++;
}

char	*remove_all_quotes(const char *input)
{
    if (!input || !*input) {
        return strdup("");
    }
    int len = strlen(input);
    char* work = strdup(input);
    if (!work)
		return NULL;
    char* result = malloc(len + 1);
    if (!result) {
        free(work);
        return NULL;
    }
    int result_pos = 0;
    for (int i = 0; i < len; i++)
	{
        if (work[i] == '\'')
		{
            int end = i + 1;
            while (end < len && work[end] != '\'')
			{
                end++;
            }
            if (end < len)
			{
                for (int j = i + 1; j < end; j++)
				{
                    result[result_pos++] = work[j];
                }
                i = end;
            }
			else
                result[result_pos++] = work[i];
        }
        else if (work[i] == '"')
		{
            int end = i + 1;
            while (end < len && work[end] != '"')
                end++;
            if (end < len)
			{
                for (int j = i + 1; j < end; j++)
				{
                    result[result_pos++] = work[j];
                }
                i = end;
            }
			else
                result[result_pos++] = work[i];
        }
        else
            result[result_pos++] = work[i];
    }
    result[result_pos] = '\0';
    free(work);
    return result;
}

char	*ft_expand(t_obj *obj, char *str)
{
	char	**argv;
	int		i;

	i = 0;
	if (str == NULL || ft_strcmp(str, "") == 0)
		return (ft_strdup(""));
	argv = ft_split(str, ' ');
	free(str);
	str = NULL;
	while (argv[i])
	{
		if (ft_strrchr(argv[i], '$'))
		{
			str = ft_strjoin2(str, get_value(obj, argv[i] + 1), 2);
			free(argv[i]);
		}
		else
			str = ft_strjoin2(str, argv[i], 2);
		i++;
	}
	free(argv);
	return (str);
}
