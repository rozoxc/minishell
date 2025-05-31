/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:39:34 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/31 12:00:28 by hfalati          ###   ########.fr       */
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
	if (!buffer)
		return (NULL);
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
	int		no_new_line;
	int		size;
	int		start_idx;
	char	**str;

	str = arg;
	start_idx = 1;
	if (obj->echo_flag == 1)
	{
		str = ft_split_export(arg[1], ' ');
		size = ft_size(str);
		start_idx = 0;
	}
	else
		size = ft_size(str);
	parse_echo_args(&str, &start_idx, &no_new_line, size);
	echo_print_args(str, start_idx, size, no_new_line);
	if (obj->echo_flag == 1)
		clean_echo(str);
	obj->echo_flag = 0;
	return (determine_exit_code(obj, 0), SUCCESS);
}
