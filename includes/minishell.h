/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:17:32 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/26 18:47:47 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"

# define SUCCESS 0
# define FAILURE -1
# define Q_ERROR 127
# define SYNTAX_ERRROR 2

# define EMPTY 0
# define COMMAND 1
# define ARG 3
# define APPEND 4 // >>
# define INPUT 5 // <
# define TRUNC 6 // >
# define HEREDOC 7 // <<
# define PIPE 8 // |

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
	char			**argv;
	char			*intfile;
	char			*outfile;
	int				append;
	int				heredoc;
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

//executed utils functions
int		determine_exit_code(t_obj *obj, int exit_code);
void	pipe_error(t_obj *obj, int pid);
int		fork_error(t_obj *obj, int pid);
int		dup_error(t_obj *obj, int dup);
void	dup2_error(t_obj *obj, int dup);
void	close_fds(int fd1, int fd2);
int		count_cmds(t_obj *obj);
char	*get_path(t_obj *obj, char *cmd);
int		execute(t_obj *obj);
void	ft_wait_all(t_obj *obj);
int		ft_heredoc(t_obj *obj);
int		set_redirections(t_cmd *cmd);
char	**ft_split_simple(char const *str, char charset);

// parsing utlis function
int		parsing(t_obj *obj);
t_cmd	*create_list(t_token *token);
int		alloc_mem(char *str);
void	append_token(t_token **token, char *str);
void	skip_space(char **str);
int		check_sep(char **str, char c);
char	set_char(char **str, char c);
int		syntax(t_token *token);
void	expand(t_obj *obj);
void	append_lexer(t_lexer **lexer, char *str, int i);
void	append_argv(t_cmd **cmd, t_lexer *lexer, char **argv);

//builtuin function
int		ft_export(char	**av, t_obj *obj);
int		ft_echo(char	**arg, t_obj *obj);
int		ft_env(t_obj	*obj);
int		ft_pwd(char		**argv, t_obj *obj);
int		ft_exit(char	**args);
int		ft_unset(char	**args, t_obj *obj);
int		ft_cd(char		**args, t_obj *obj);

// free
void	free_argv(char **argv);
void	free_lexer(t_lexer **lexer);
void	free_token(t_token **token);
void	free_cmd(t_cmd **cmd);
void	free_env(t_env **env);

// utlis
char	*get_value(t_obj *obj, char *str);
int		check_build(char *cmd);
int		check_build(char *cmd);
int		run_build(t_obj *obj, char **cmd);
char	**env_to_array(t_env *env);
void	add_env(char *str, t_env **env);
void	get_env(t_env **env, char *str);
int		check_fond(char *str);
void	shell_level(t_obj *obj);
//signals
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	signal_handler(void);
void	hide_ctrl_characters(void);
#endif
