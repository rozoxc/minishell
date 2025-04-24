/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:00:21 by hfalati           #+#    #+#             */
/*   Updated: 2025/04/24 12:53:25 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t  count_words(const char *s, char delim) {
    size_t  count = 0;
    int     in_quote = 0;
    char    quote_char = 0;

    while (*s) {
        // skip delimiters
        while (*s == delim)
            s++;
        if (!*s)
            break;
        count++;
        // walk until next delimiter that's not inside quotes
        while (*s) {
            if (in_quote) {
                if (*s == quote_char) {
                    in_quote = 0;
                    quote_char = 0;
                }
            } else {
                if (*s == '\'' || *s == '"') {
                    in_quote = 1;
                    quote_char = *s;
                } else if (*s == delim) {
                    break;
                }
            }
            s++;
        }
    }
    return count;
}

// Extract one word, return its length (without outer quotes)
static size_t  word_len(const char *s, char delim) {
    size_t  len = 0;
    int     in_quote = 0;
    char    quote_char = 0;

    // count until next delim outside quotes
    while (s[len]) {
        if (in_quote) {
            if (s[len] == quote_char)
                in_quote = 0;
        } else {
            if (s[len] == '\'' || s[len] == '"') {
                in_quote = 1;
                quote_char = s[len];
                // don’t count the quote itself in length
                len++;
                continue;
            } else if (s[len] == delim) {
                break;
            }
        }
        len++;
    }
    return len;
}

static void free_split(char **arr, size_t used) {
    while (used--)
        free(arr[used]);
    free(arr);
}

char    **ft_split(const char *s, char delim) {
    size_t  words = count_words(s, delim);
    char    **res = malloc((words + 1) * sizeof *res);
    size_t  i = 0;

    if (!res)
        return NULL;
    while (i < words) {
        size_t  len;
        char    *token;
        char    *dst;

        // skip leading delimiters
        while (*s == delim)
            s++;
        // figure out how long this word is
        len = word_len(s, delim);
        token = malloc(len + 1);
        if (!token) {
            free_split(res, i);
            return NULL;
        }
        // copy it, *stripping* any outer quotes
        dst = token;
        {
            size_t j = 0;
            int    in_quote = 0;
            char   quote_char = 0;
            while (j < len) {
                if (!in_quote && (s[j] == '\'' || s[j] == '"')) {
                    in_quote = 1;
                    quote_char = s[j];
                } else if (in_quote && s[j] == quote_char) {
                    in_quote = 0;
                } else {
                    *dst++ = s[j];
                }
                j++;
            }
        }
        *dst = '\0';
        res[i++] = token;
        s += len;
    }
    res[i] = NULL;
    return res;
}