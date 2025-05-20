/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utlis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:50:57 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/20 20:55:49 by hfalati          ###   ########.fr       */
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

char	*get_parent_dir(const char *pwd)
{
	char	*slash;

	slash = ft_strrchr(pwd, '/');
	if (!slash || slash == pwd)
		return (ft_strdup("/"));
	return (ft_substr(pwd, 0, slash - pwd));
}

int	cd_no_perm(t_obj *obj, char **av)
{
	char	*new_pwd;
	int		fd;

	fd = open("/..", O_RDONLY | O_DIRECTORY);
	if (!ft_strcmp("..", av[1]) && fd != -1)
	{
		close(fd);
		update_oldpwd(&obj->tool.oldpwd, &obj->tool.pwd);
		new_pwd = get_parent_dir(obj->tool.pwd);
		if (!new_pwd)
			return (determine_exit_code(obj, 1), FAILURE);
		free(obj->tool.pwd);
		obj->tool.pwd = new_pwd;
		ft_chdir(obj->tool.pwd, obj);
		determine_exit_code(obj, 0);
	}
	else
	{
		if (fd != -1)
			close(fd);
		ft_chdir(av[1], obj);
	}
	return (SUCCESS);
}

int	ft_chdir(char *path, t_obj *obj)
{
	if (chdir(path) != 0)
	{
		if (errno == EACCES)
			ft_putstr_fd("cd: permission denied\n", 2);
		else
			ft_putstr_fd("cd: no such file or directory\n", 2);
		determine_exit_code(obj, 1);
		return (FAILURE);
	}
	return (SUCCESS);
}
