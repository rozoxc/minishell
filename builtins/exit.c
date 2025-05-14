/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:23:14 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/14 11:24:22 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **args, t_obj *obj)
{
	int	exit_status;

	if (obj->flag != 1)
		printf("exit\n");
	if (args[1] == NULL)
		exit(SUCCESS);
	if (!ft_is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd("numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (args[2] != NULL)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_status = ft_atoi(args[1]);
	exit(exit_status);
}
