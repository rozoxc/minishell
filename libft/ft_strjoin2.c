/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:47:14 by hfalati           #+#    #+#             */
/*   Updated: 2025/04/11 17:47:16 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2, int n)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (n != 3)
		free(s1);
	if (n > 1)
		free(s2);
	return (str);
}