/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:42 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/26 18:40:00 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_env(t_env **env, char *str)
{
	t_env	*tmp_env;

	tmp_env = *env;
	if (!tmp_env)
	{
		(*env) = malloc(sizeof(t_env));
		if (!*env)
			return ;
		(*env)->value = ft_strdup(str);
		(*env)->prev = NULL;
		(*env)->next = NULL;
	}
	else
	{
		while (tmp_env->next)
			tmp_env = tmp_env->next;
		tmp_env->next = malloc(sizeof(t_env));
		if (!tmp_env->next)
			return ;
		tmp_env->next->value = ft_strdup(str);
		tmp_env->next->prev = tmp_env;
		tmp_env->next->next = NULL;
	}
}

void	fill_obj(t_obj *obj, char *pwd)
{
	obj->str = NULL;
	obj->tool.pwd = ft_strdup(pwd);
	obj->tool.oldpwd = ft_strdup(pwd);
	obj->exit_code = 0;
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = NULL;
}

void	init_obj(t_obj *obj, char **env)
{
	char	pwd[PATH_MAX];
	char	pwd_var[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	fill_obj(obj, pwd);
	if (!env || !*env)
	{
		ft_strcpy(pwd_var, "PWD=");
		ft_strcat(pwd_var, pwd);
		get_env(&obj->env, pwd_var);
		get_env(&obj->env, "SHLVL=1");
		get_env(&obj->env, "_=/usr/bin/env");
		get_env(&obj->env, "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	}
	else
	{
		while (*env)
		{
			get_env(&obj->env, *env);
			env++;
		}
	}
}

int get_signal;

int	main(int args, char **argv, char **env)
{
	t_obj	obj;

	if (args == 2 || argv[1] != NULL)
		return (printf("error \n"), 1);
	init_obj(&obj, env);
	shell_level(&obj);
	while (1)
	{
		if (!isatty(0) || !isatty(1))
			return (0);
		signal_handler();
		hide_ctrl_characters();
		obj.str = readline("minishell-1.0$~ ");
		if (get_signal == 2)
		{
			determine_exit_code(&obj, 1);
			get_signal = 0;
		}
		if (obj.str == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		parsing(&obj);
		if(*obj.str)
			add_history(obj.str);
		execute(&obj);
		free(obj.str);
		free_cmd(&obj.cmd);
	}
	return (0);
}
