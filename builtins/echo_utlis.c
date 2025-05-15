/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utlis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:25:48 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/15 11:26:53 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_size(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}

int	check_flag(char *str)
{
	int	i;

	if (ft_strcmp(str, "-n") != 0 && ft_strncmp(str, "-n", 2) != 0)
		return (0);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
