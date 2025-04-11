#include "../includes/minishell.h"

void sigint_handler(int sig)
{
	(void)sig; // this canst for pass the error "unused parameter"
	rl_on_new_line(); // This tells Readline that a new line has started
	rl_replace_line("\n", 0); // This replaces the current input line with the string "\n"
	rl_redisplay(); // makes the terminal look clean after something l	ike Ctrl+C
}

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
	char pwd[200];

	getcwd(pwd, 200);
	obj->str = NULL;
	obj->tool.pwd = ft_strdup(pwd);
	obj->tool.oldpwd = ft_strdup(pwd);
	obj->exit_code = 0;
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = NULL;
	while (*env)
	{
		get_env(&obj->env, *env);
		env++;
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
		signal(SIGINT, sigint_handler); // this for in the test click ctrl + C
    	obj.str = readline("minishell-> ");
		if (obj.str == NULL) // This happens on Ctrl+D (EOF)
		{
			printf("exit\n");
			exit(0);
		}
		parsing(&obj);
		add_history(obj.str);
		execute(&obj, env);
		free(obj.str);
		free(obj.cmd);
	}
	return 0;
}
