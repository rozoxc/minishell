/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:16:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/27 23:04:50 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(char **argv, t_obj *obj)
{
	char	path[200];

	(void)obj;
	(void)argv;
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd");
		return (FAILURE);
	}
	printf("%s\n", path);
	return (SUCCESS);
}
