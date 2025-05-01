/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:00:21 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/01 13:46:16 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_skip(const char **str)
{
    if (**str != '\0')
    {
        (*str)++;
        return (1);
    }
    return (0);
}

int ft_sep2(char c)
{
    return (c == '$' || c == '\'' || c == '\"');
}

int dollar_len(const char **str)
{
    if ((*str)[0] == '$' && (*str)[1] == '$')
    {
        *str += 2;
        return (2);
    }
    return (0);
}

static int word_len(const char *s, char c)
{
    int len = 0;

    if ((s[0] == '\'' || s[0] == '\"') && ft_skip(&s))
        return (1);
    if (s[0] == c)
    {
        if (c == ' ')
            return 1;
        while (s[len] == c)
            len++;
        return len;
    }
    int dl;
    if ((dl = dollar_len(&s)) > 0)
        return dl;
    if (*s == '$' && ft_skip(&s))
        len++;
    while (*s && *s != c && !ft_sep2(*s))
    {
        len++;
        s++;
    }
    return len;
}

static int count_words(const char *s, char c)
{
    int count = 0;
    while (*s)
    {
        if (*s == c)
        {
            if (c == ' ')
            {
                s++;
                count++;
            }
            else
            {
                while (*s == c)
                    s++;
                count++;
            }
        }
        else if (*s == '\'' || *s == '\"')
        {
            ft_skip(&s);
            count++;
        }
        else
        {
            int dl = dollar_len(&s);
            if (dl > 0)
            {
                count++;
                continue;
            }
            if (*s == '$')
                ft_skip(&s);
            while (*s && *s != c && !ft_sep2(*s))
                s++;
            count++;
        }
    }
    return count;
}

static void free_split(char **arr, int n)
{
    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}

char **ft_split(const char *s, char c)
{
    int   total = count_words(s, c);
    char **arr  = malloc((total + 1) * sizeof(char *));
    if (!arr) return NULL;

    for (int i = 0; i < total; i++)
    {
        int len = word_len(s, c);
        arr[i]  = malloc(len + 1);
        if (!arr[i])
        {
            free_split(arr, i);
            return NULL;
        }
        ft_strncpy(arr[i], s, len);
        arr[i][len] = '\0';
        s += len;
    }
    arr[total] = NULL;
    return arr;
}