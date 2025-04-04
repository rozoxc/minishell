/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:36:48 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/05 08:42:03 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_str(size_t len)
{
	char	*str;

	str = (char *)malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	novel_len;
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	novel_len = ft_strlen(s);
	if (start >= novel_len)
		return (allocate_str(0));
	if (len > novel_len - start)
		len = novel_len - start;
	str = allocate_str(len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
