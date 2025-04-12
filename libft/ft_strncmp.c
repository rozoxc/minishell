/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:52 by hfalati           #+#    #+#             */
/*   Updated: 2025/04/12 17:53:18 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	j;

	j = 0;
	while (n > 0 && s1[j] && s2[j] && s1[j] == s2[j])
	{
		j++;
		n--;
	}
	if (n == 0 || (s1[j] == '\0' && s2[j] == '\0'))
	{
		return (0);
	}
	else
	{
		return ((unsigned char)s1[j] - (unsigned char)s2[j]);
	}
}
