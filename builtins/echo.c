/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:39:34 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/27 22:06:41 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_strcmp1(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_size(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}

static void	echo_print_args(char **arg, int start_idx, \
	int size, int no_new_line)
{
	int	i;

	i = start_idx;
	while (i < size)
	{
		ft_putstr(arg[i]);
		if (i < size - 1)
			write(1, " ", 1);
		i++;
	}
	if (!no_new_line)
		write(1, "\n", 1);
}

int	ft_echo(char **arg, t_obj *obj)
{
	int	no_new_line;
	int	size;
	int	i;

	(void)obj;
	i = 1;
	size = ft_size(arg);
	no_new_line = 0;
	if (arg[1] != NULL && ft_strcmp1(arg[1], "-n") == 0)
	{
		no_new_line = 1;
		i = 2;
	}
	echo_print_args(arg, i, size, no_new_line);
	return (EXIT_SUCCESS);
}
