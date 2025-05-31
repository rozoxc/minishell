/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:23:14 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/31 11:33:22 by hfalati          ###   ########.fr       */
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

void	show_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

char	*skip_zero(char *str)
{
	int		i;
	char	*p;
	int		j;

	j = 0;
	i = 0;
	if (str[i] != '0')
		return (str);
	p = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!p)
		return (NULL);
	while (str[i] == '0')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		p[j] = str[i];
		j++;
		i++;
	}
	p[j] = '\0';
	return (p);
}

int	ft_is_valid(char *str)
{
	int		n;
	char	*new_str;

	new_str = skip_zero(str);
	n = ft_atoi(str);
	if (!ft_strcmp(new_str, "9223372036854775807"))
	{
		free(str);
		return (1);
	}
	if (n == -1)
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

int	ft_exit(char **args, t_obj *obj)
{
	int	exit_status;

	if (obj->flag != 1)
		ft_putstr_fd("exit\n", 1);
	if (args[1] == NULL)
	{
		exit(obj->exit_code);
	}
	else if (args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (determine_exit_code(obj, 1), 1);
	}
	else if (!ft_is_numeric(args[1]) || !ft_is_valid(args[1]))
	{
		show_error(args[1]);
		exit(255);
	}
	else if (args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_status = ft_atoi(args[1]);
	exit(exit_status);
}
