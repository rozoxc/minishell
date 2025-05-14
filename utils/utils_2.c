/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:21:41 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/14 18:19:17 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_error(t_obj *obj, int fd1, int fd2, char *file)
{
	unlink(file);
	if (fd1 == -1 || fd2 == -1)
	{
		ft_putstr_fd("file to open the file\n", 2);
		if (fd1 != -1)
			close(fd1);
		if (fd2 != -1)
			close (fd2);
		exit(determine_exit_code(obj, 1));
	}
}
