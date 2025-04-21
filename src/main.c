#include "../includes/minishell.h"

void sigint_handler(int sig)
{
	(void)sig; // this canst for pass the error "unused parameter"
	write(STDOUT_FILENO, "\n", 1);  // Print a newline
    rl_replace_line("", 0);         // Clear the line buffer
    rl_on_new_line();               // Move to the new line
    rl_redisplay();                 // Display the prompt
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
    if (!env || !*env) {
        char pwd_var[256];
        snprintf(pwd_var, sizeof(pwd_var), "PWD=%s", pwd);
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
		signal(SIGINT, sigint_handler); // this for in the test click ctrl + C
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
		free(obj.cmd);
	}
	return 0;
}
