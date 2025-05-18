/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:50:24 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/18 00:21:49 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) != 0)
		return (-1);
	if (ft_strncmp(s2, s1, ft_strlen(s2)) != 0)
		return (-1);
	return (0);
}
