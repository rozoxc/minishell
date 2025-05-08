/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:53 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/07 22:52:18 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Change directory and handle errors */
int	ft_chdir(char *path)
{
	if (chdir(path) != 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (FAILURE);
	}
	return (SUCCESS);
}

/* Handle cd with no arguments (cd to HOME) */
int	cd_no_av(t_obj *obj)
{
	char	*pwd;
	char	old_pwd[PATH_MAX];

	pwd = ft_getenv(obj->env, "HOME");
	if (!pwd)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (FAILURE);
	}
	if (!getcwd(old_pwd, PATH_MAX))
		return (FAILURE);
	if (ft_chdir(pwd) != 0)
		return (FAILURE);
	obj->tool.pwd = pwd;
	return (SUCCESS);
}

/* Handle the case when getcwd fails */
int	handle_getcwd_failure(char **av, t_obj *obj, char *pwd)
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
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	return (SUCCESS);
}

/* Handle normal cd to directory */
void	cd_to_dir(char *dir, t_obj *obj)
{
	char	pwd[PATH_MAX];

	ft_chdir(dir);
	free(obj->tool.oldpwd);
	obj->tool.oldpwd = ft_strdup(obj->tool.pwd);
	free(obj->tool.pwd);
	getcwd(pwd, PATH_MAX);
	obj->tool.pwd = ft_strdup(pwd);
}

/* Main cd function */
int	ft_cd(char **av, t_obj *obj)
{
	char	pwd[PATH_MAX];

	if (av[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (FAILURE);
	}
	if (!getcwd(pwd, PATH_MAX))
		return (handle_getcwd_failure(av, obj, pwd));
	else if (!av[1])
	{
		if (cd_no_av(obj) == FAILURE)
			return (FAILURE);
	}
	else
		cd_to_dir(av[1], obj);
	update_env(obj);
	return (SUCCESS);
}
