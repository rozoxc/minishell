/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:55:33 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/04 13:56:41 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	i = 0;
	sl = 0;
	dl = 0;
	if (!dst && !dstsize)
		return (ft_strlen(src));
	while (dst[dl] && dl < dstsize)
		dl++;
	while (src[sl])
		sl++;
	if (dl >= dstsize)
		return (dstsize + sl);
	while (src[i] && ((dl + i) < dstsize - 1))
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return (dl + sl);
}
