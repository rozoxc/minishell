/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:00:21 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/31 11:18:10 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    word_len(const char *s, char c)
{
    int    len;
    int    dl;

    len = 0;
    if ((s[0] == '\'' || s[0] == '\"') && ft_skip(&s))
        return (1);
    if (s[0] == c)
    {
        if (c == ' ')
            return (1);
        while (s[len] == c)
            len++;
        return (len);
    }
    dl = dollar_len(&s);
    if (dl > 0)
        return (dl);
    if (*s == '$' && ft_skip(&s))
        len++;
    while (*s && *s != c && !ft_sep2(*s))
    {
        len++;
        s++;
    }
    return (len);
}

int    handle_quotes_and_dollar(const char **s, char c)
{
    int    count;
    int    dl;

    count = 0;
    if (**s == '\'' || **s == '\"')
    {
        ft_skip(s);
        count++;
    }
    else
    {
        dl = dollar_len(s);
        if (dl > 0)
        {
            count++;
            return (count);
        }
        if (**s == '$')
            ft_skip(s);
        while (**s && **s != c && !ft_sep2(**s))
            (*s)++;
        count++;
    }
    return (count);
}

int    handle_special_cases(const char **s, char c)
{
    int    count;

    count = 0;
    if (**s == c)
    {
        if (c == ' ')
        {
            (*s)++;
            count++;
        }
        else
        {
            while (**s == c)
                (*s)++;
            count++;
        }
    }
    else
    {
        count = handle_quotes_and_dollar(s, c);
    }
    return (count);
}

int    count_words(const char *s, char c)
{
    int    count;

    count = 0;
    while (*s)
        count += handle_special_cases(&s, c);
    return (count);
}

char    **ft_split(const char *s, char c)
{
    int        i;
    int        len;
    int        total;
    char    **arr;

    total = count_words(s, c);
    arr = malloc((total + 1) * sizeof(char *));
    if (!arr)
        return (NULL);
    i = -1;
    while (++i < total)
    {
        len = word_len(s, c);
        arr[i] = malloc(len + 1);
        if (!arr[i])
        {
            free_split(arr, i);
            return (NULL);
        }
        ft_strncpy(arr[i], s, len);
        arr[i][len] = '\0';
        s += len;
    }
    arr[total] = NULL;
    return (arr);
}
