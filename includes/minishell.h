/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:17:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/09 13:17:32 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include "../libft/libft.h"

// # define SUCCESS 0
// # define FAILURE -1
// # define Q_ERROR 130
// # define SYNTAX_ERRROR 1

// # define EMPTY 0
// # define COMMAND 1
// # define ARG 3
// # define APPEND 4 // >>
// # define INPUT 5 // <
// # define TRUNC 6 // >
// # define HEREDOC 7 // <<
// # define PIPE 8 // |

//parsing structs

typedef enum s_token_type{
	PIPE,
	REDIRECT_APPEND,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	WORD,
} t_token_type;

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

typedef struct s_cmd
{
	char	**argv;
	char	*intfile;
	char	*outfile;
	int		append;
	int 	heredoc;
	t_lexer			*lexer;
	struct s_cmd	*next;
	struct s_cmd	*prev;
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

//parsing functions
t_token	*main_parser(char *input);
t_token	*lexer(char *input);
t_cmd	*parse_tokens(t_token *tokens);
void parsing(t_obj *obj);

//executed utils functions
int		determine_exit_code(t_obj *obj, int exit_code);
void	pipe_error(t_obj *obj, int pid);
int		fork_error(t_obj *obj, int pid);
int		dup_error(t_obj *obj, int dup);
void	dup2_error(t_obj *obj, int dup);
void	close_fds(int fd1, int fd2);
int		count_cmds(t_obj *obj);
char	*validate_and_get_path(char **command, char **envp);
int		execute(t_obj *obj, char **env);
void ft_wait_all(t_obj *obj, int *status);

#endif