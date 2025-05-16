/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:39:34 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/16 15:59:37 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	calcul_buffer_size(char **arg, int start_idx, int size)
{
	int	i;
	int	total_size;

	total_size = 0;
	i = start_idx;
	while (i < size)
	{
		total_size += ft_strlen(arg[i]);
		if (i < size - 1)
			total_size += 1;
		i++;
	}
	return (total_size + 1);
}

char	*allocate_echo_buffer(char **arg, int start_idx, int size
		, int no_new_line)
{
	int		buffer_size;
	char	*buffer;

	buffer_size = calcul_buffer_size(arg, start_idx, size);
	if (no_new_line == 0)
		buffer_size += 1;
	buffer = malloc(sizeof(char) * buffer_size);
	return (buffer);
}

int	fill_echo_buffer(char **arg, char *buffer, int start_idx, int size)
{
	int	i;
	int	buffer_pos;
	int	arg_len;

	buffer_pos = 0;
	i = start_idx;
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
	return (buffer_pos);
}

void	echo_print_args(char **arg, int start_idx, int size, int no_new_line)
{
	int		buffer_pos;
	char	*buffer;

	buffer = allocate_echo_buffer(arg, start_idx, size, no_new_line);
	if (!buffer)
		return ;
	buffer_pos = fill_echo_buffer(arg, buffer, start_idx, size);
	if (no_new_line == 0)
	{
		buffer[buffer_pos] = '\n';
		buffer_pos++;
	}
	buffer[buffer_pos] = '\0';
	write(1, buffer, buffer_pos);
	free(buffer);
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
