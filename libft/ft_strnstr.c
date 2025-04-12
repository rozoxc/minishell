/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:50:34 by hfalati           #+#    #+#             */
/*   Updated: 2025/04/12 18:37:08 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t		needle_len;
	size_t		haystack_len;
	size_t		i;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	haystack_len = ft_strlen(haystack);
	if (needle_len > haystack_len || n < needle_len)
		return (NULL);
	while (i <= haystack_len - needle_len && i + needle_len <= n)
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
