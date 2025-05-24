/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utlis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:00:10 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/24 22:40:49 by hfalati          ###   ########.fr       */
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

void clean_echo(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	parse_echo_args(char ***str, int *id, int *no_new_line, int size)
{
	*no_new_line = 0;
	while (*id < size && check_flag((*str)[*id]))
	{
		*no_new_line = 1;
		(*id)++;
	}
}
