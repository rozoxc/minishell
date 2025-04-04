#include "../includes/minishell.h"

void sigint_handler(int sig)
{
	(void)sig; // this canst for pass the error "unused parameter"
	rl_on_new_line(); // This tells Readline that a new line has started
	rl_replace_line("\n", 0); // This replaces the current input line with the string "\n"
	rl_redisplay(); // makes the terminal look clean after something like Ctrl+C
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
	// whie (*env)
	// {
	// 	//here function for set the env
	// }
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
		obj.str = readline("minishell : ");
		parsing(&obj); // sir kad parsing rah dart wahad file smito trush fih dakchi li kanti dayar latkhasak chi7aja  
		// here add history
		executor(&obj, env); // hadi dyali sir 9awad rah kadit file parsing matzid walo hna wla kad signal wla history
		// here we build a claen function 
	}
	return 0;
}
