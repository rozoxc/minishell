#include "../includes/minishell.h"


int	main(int args, char **argv, char **env)
{
	t_obj	obj;

    if (args == 2 || argv[1] != NULL)
	{
		printf("error : minishell accepts no argumnets.\n");
		return (1);
	}
	// here build function to intit the obj
	while (1)
	{
		// GPT here the signal function
		obj.str = readline("minishell : ");
		parsing(&obj); // sir kad parsing 
		// here add history
		executor(&obj, env); // hadi dyali sir 9awad rah kadit file parsing matzid walo hna wla kad signal wla history
		// here we build a claen function 
	}
	return 0;
}