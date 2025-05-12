/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utlis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:50:57 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/11 21:34:36 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(t_obj *obj)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD=");
	oldpwd = ft_strdup("OLDPWD=");
	pwd = ft_strjoin2(pwd, obj->tool.pwd, 1);
	oldpwd = ft_strjoin2(oldpwd, obj->tool.oldpwd, 1);
	add_env(pwd, &obj->env);
	add_env(oldpwd, &obj->env);
	free(pwd);
	free(oldpwd);
}

void	update_oldpwd(char **s1, char **s2)
{
	free(*s1);
	*s1 = ft_strdup(*s2);
}
