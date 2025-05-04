/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:53 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/04 22:36:31 by hfalati          ###   ########.fr       */
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

int	ft_chdir(char *path)
{
	if (chdir(path) != 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	cd_no_av(t_obj *obj)
{
	char	*pwd;
	char	old_pwd[PATH_MAX];

	pwd = ft_getenv(obj->env, "HOME");
	if (!pwd)
		return(ft_putstr_fd("cd: HOME not set\n", 2), FAILURE);
	if (!getcwd(old_pwd, PATH_MAX))
		return(FAILURE);
	if (ft_chdir(pwd) != 0)
		return (FAILURE);
	obj->tool.pwd = pwd;
	return (SUCCESS);
}

int	ft_cd(char **av, t_obj *obj)
{
	char	pwd[PATH_MAX];
	int		i;

	if (av[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			return (FAILURE);
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		if (!ft_strcmp("..", av[1]))
		{
			update_oldpwd(&obj->tool.oldpwd, &obj->tool.pwd);
			obj->tool.pwd = ft_strjoin2(obj->tool.pwd, "/..", 1);
		}
		else if (!ft_strcmp(".", av[1]))
		{
			update_oldpwd(&obj->tool.oldpwd, &obj->tool.pwd);
			obj->tool.pwd = ft_strjoin2(obj->tool.pwd, "/.", 1);
		}
		ft_chdir(av[1]);
		if (getcwd(pwd, PATH_MAX))
		{
			free(obj->tool.pwd);
			obj->tool.pwd = NULL;
			obj->tool.pwd = ft_strdup(pwd);
		}
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
	}
	else if (!av[1])
	{
		if (cd_no_av(obj) == FAILURE)
			return (FAILURE);
	}
	else
	{
		ft_chdir(av[1]);
		free(obj->tool.oldpwd);
		obj->tool.oldpwd = ft_strdup(obj->tool.pwd);
		free(obj->tool.pwd);
		getcwd(pwd, PATH_MAX);
		obj->tool.pwd = ft_strdup(pwd);
	}
	update_env(obj);
	return (SUCCESS);
}
