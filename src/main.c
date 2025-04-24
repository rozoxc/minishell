/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:30:42 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/24 10:30:42 by ababdoul         ###   ########.fr       */
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

void	init_obj(t_obj *obj, char **env)
{
	char pwd[PATH_MAX];
	char pwd_var[PATH_MAX];

	getcwd(pwd, 200);
	obj->str = NULL;
	obj->tool.pwd = ft_strdup(pwd);
	obj->tool.oldpwd = ft_strdup(pwd);
	obj->exit_code = 0;
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = NULL;
	if (!env || !*env) {
		strcpy(pwd_var, "PWD=");
        strcat(pwd_var, pwd);
		get_env(&obj->env, pwd_var);
		get_env(&obj->env, "SHLVL=1");
		get_env(&obj->env, "_=/usr/bin/env");
		get_env(&obj->env, "PATH=/bin/");
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

int	main(int args, char **argv, char **env)
{
	t_obj	obj;

	if (args == 2 || argv[1] != NULL)
	{
		printf("error : minishell accepts no argumnets.\n");
		return (1);
	}
	init_obj(&obj, env);
	while (1)
	{
		signal_handler();
		hide_ctrl_characters();
		obj.str = readline("minishell-1.0$~ ");
		if (obj.str == NULL) // This happens on Ctrl+D (EOF)
		{
			printf("exit\n");
			exit(0);
		}
		parsing(&obj);
		add_history(obj.str);
		execute(&obj);
		free(obj.str);
		free_cmd(&obj.cmd);
	}
	return 0;
}
