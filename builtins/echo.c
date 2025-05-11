/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:39:34 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/11 15:47:51 by ababdoul         ###   ########.fr       */
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
int calcul_buffer_size(char **arg, int start_idx, int size)
{
	int i;
	int total_size;

	i = start_idx;
	while (i < size)
	{
		total_size = ft_strlen(arg[i]);
		if (i < size - 1)
			total_size +=  1;
		i++;
	}
	return (total_size + 1);
}

static void	echo_print_args(char **arg, int start_idx, int size,
		int no_new_line)
{
	int	i;
	char *buffer;
	int buffer_pos;
	int buffer_size;
	int arg_len;

	buffer_size = calcul_buffer_size(arg, start_idx, size);
	if (no_new_line == 0)
		buffer_size += 1;
	i = start_idx;
	buffer_pos = 0;
	buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return ;
	while (i < size)
	{
		arg_len = ft_strlen(arg[i]);
		ft_memcpy(&buffer[buffer_pos], arg[i], arg_len);
		buffer_pos += arg_len;
		if (i < size - 1)
		{
			buffer[buffer_pos] = ' ';
			buffer_pos++;
		}
		i++;
	}
	if (no_new_line == 0)
	{
		buffer[buffer_pos] = '\n';
		buffer_pos++;
	}
	buffer[buffer_pos] = '\0';
	write(1, buffer, buffer_pos);
	free(buffer);
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

int	ft_echo(char **arg, t_obj *obj)
{
	int	no_new_line;
	int	size;
	int	start_idx;

	(void)obj;
	size = ft_size(arg);
	no_new_line = 0;
	start_idx = 1;
	while (start_idx < size && check_flag(arg[start_idx]))
	{
		no_new_line = 1;
		start_idx++;
	}
	echo_print_args(arg, start_idx, size, no_new_line);
	return (EXIT_SUCCESS);
}
