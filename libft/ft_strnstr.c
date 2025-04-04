/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:50:34 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/06 14:23:52 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *n, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	nlen = ft_strlen(n);
	if (nlen == 0)
		return ((char *)hs);
	if (len == 0)
		return (NULL);
	i = 0;
	while (i + nlen <= len && hs[i] != '\0')
	{
		j = 0;
		while (j < nlen && hs[i + j] == n[j] && (i + j) < len)
			j++;
		if (j == nlen)
			return ((char *)(hs + i));
		i++;
	}
	return (NULL);
}
