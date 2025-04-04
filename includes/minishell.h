#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
#include <signal.h>

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	char			*str;
	int				i;
	struct s_lexer	*next;
}	t_lexer;

typedef struct t_cmd
{
	char			**argv;
	t_lexer			*lexer;
	struct t_cmd	*next;
	struct t_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_tool
{
	char	*pwd;
	char	*oldpwd;
}	t_tool;

typedef struct s_obj
{
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env;
	t_tool	tool;
	char	*str;
	int		*pid;
	int		exit_code;
}	t_obj;

typedef struct s_bulding
{
	char	*str;
	int		(*function)(char **argv, t_obj *obj);
}	t_bulding;


#endif