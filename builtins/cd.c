/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:53 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/19 22:27:36 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_no_av(t_obj *obj)
{
	char	old_pwd_buf[PATH_MAX];
	char	*home;

	home = ft_getenv(obj->env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (determine_exit_code(obj, 1), FAILURE);
	}
	if (chdir(home) == FAILURE)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(home, 2);
		return (FAILURE);
	}
	if (!getcwd(old_pwd_buf, PATH_MAX))
		return (FAILURE);
	free(obj->tool.oldpwd);
	obj->tool.oldpwd = ft_strdup(old_pwd_buf);
	free(obj->tool.pwd);
	obj->tool.pwd = ft_strdup(home);
	return (SUCCESS);
}

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
	if (ft_chdir(av[1], obj) == FAILURE)
		return (FAILURE);
	if (getcwd(pwd, PATH_MAX))
	{
		free(obj->tool.pwd);
		obj->tool.pwd = NULL;
		obj->tool.pwd = ft_strdup(pwd);
	}
	else
		ft_putstr_fd("cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n", 2);
	return (determine_exit_code(obj, 0), SUCCESS);
}

int	handle_cd_getcwd_failure(char **av, t_obj *obj, char *pwd)
{
	int	fd;

	if (errno == EACCES)
	{
		fd = open(".", O_RDONLY | O_DIRECTORY);
		if (fd == -1 && errno == EACCES)
		{
			if (cd_no_perm(obj) == FAILURE)
				return (FAILURE);
		}
		else
		{
			if (fd != -1)
				close(fd);
			if (handle_getcwd_failure(av, obj, pwd) == FAILURE)
				return (FAILURE);
		}
	}
	else
	{
		if (handle_getcwd_failure(av, obj, pwd) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	cd_to_dir(char *dir, t_obj *obj)
{
	char	pwd[PATH_MAX];

	ft_chdir(dir, obj);
	free(obj->tool.oldpwd);
	obj->tool.oldpwd = ft_strdup(obj->tool.pwd);
	free(obj->tool.pwd);
	getcwd(pwd, PATH_MAX);
	obj->tool.pwd = ft_strdup(pwd);
}

int	ft_cd(char **av, t_obj *obj)
{
	char	pwd[PATH_MAX];

	if (av[1] && av[2])
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (determine_exit_code(obj, 1), FAILURE);
	}
	if (!av[1])
	{
		if (cd_no_av(obj) == FAILURE)
			return (determine_exit_code(obj, 1), FAILURE);
	}
	else if (!getcwd(pwd, PATH_MAX))
	{
		if (handle_cd_getcwd_failure(av, obj, pwd) == FAILURE)
			return (FAILURE);
	}
	else
		cd_to_dir(av[1], obj);
	update_env(obj);
	return (SUCCESS);
}
