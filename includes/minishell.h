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
# include <errno.h>
# include <sys/stat.h>

# define SUCCESS 0
# define FAILURE 1
# define Q_ERROR 127
# define SYNTAX_ERRROR 258

# define EMPTY 0
# define COMMAND 1
# define ARG 3
# define APPEND 4 // >>
# define INPUT 5 // <
# define TRUNC 6 // >
# define HEREDOC 7 // <<
# define PIPE 8 // |

int	g_signal;

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
	int				fd;
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
	t_token			*token;
	t_cmd			*cmd;
	t_env			*env;
	t_tool			tool;
	int				status;
	char			*str;
	int				*pid;
	int				flag;
	int				echo_flag;
	int				exit_code;
	int				split_expand;
	int				count_heredoc;
	int				count_env;
	int				fd_in;
	int				fd_out;
	struct termios	term;
}	t_obj;

//executed utils functions
int		determine_exit_code(t_obj *obj, int exit_code);
int		pipe_error(t_obj *obj, int pid);
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
void	cleanup_execution(t_obj *obj, int std_in, int std_out, char **env);
int		handle_double_quote(const char *str, int *i, char *res, int *pos);
int		handle_single_quote(const char *str, int *i, char *res, int *pos);
void	shift_empty_args(char *argv[]);
void	parent_process(t_obj *obj, t_cmd *curr_cmd, int fd_pipe[2]);
char	*get_command_path(t_obj *obj, char *cmd);
void	child_process_execution(t_obj *obj, char *path, \
		t_cmd *cur_cmd, char **env);
void	shift_empty_args_cmds(t_cmd *cmd);
void	shift_env_arg(char *argv[]);
void	process_input(t_obj *obj, char *s, int fd, char *stop);
void	process_input(t_obj *obj, char *s, int fd, char *stop);
int		setup_execution(t_obj *obj, int *std_in, int *std_out, char ***env);
// parsing utlis function
int		parsing(t_obj *obj);
t_cmd	*create_list(t_obj *obj);
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
int		ft_pwd(t_env *env, t_obj *obj);
int		ft_exit(char	**args, t_obj *obj);
int		ft_unset(char	**args, t_obj *obj);
int		ft_cd(char		**args, t_obj *obj);
int		check_flag(char *str);
int		ft_size(char **arg);
void	handle_special_char(void);
char	*get_parent_dir(const char *pwd);
int		cd_no_perm(t_obj *obj, char **av);
int		ft_chdir(char *path, t_obj *obj);
// free
void	free_argv(char **argv);
void	free_lexer(t_lexer **lexer);
void	free_token(t_token **token);
void	free_cmd(t_cmd **cmd);
void	free_env(t_env **env);
void	clean_echo(char **str);
// utlis
char	*get_value(t_obj *obj, char *str);
int		check_build(char *cmd);
int		run_build(t_obj *obj, char **cmd);
char	**env_to_array(t_env *env);
void	add_env(char *str, t_env **env);
void	get_env(t_env **env, char *str);
int		check_fond(char *str);
int		check_equal(char *str);
int		is_heredoc(t_cmd *cmd);
char	*remove_all_quotes(const char *s);
int		is_only_whitespace(const char *str);
char	*ft_expand(t_obj *obj, char *str);
char	*ft_getenv(t_env *env, char *key);
void	open_error(t_obj *obj, int fd1, int fd2, char *file);
void	exit_code_pipe(t_obj *obj, t_token *token);
void	count_heredoc(t_obj *obj, t_token *token);
void	export_equal(char **av, int *j, int *count);
void	fix_norm(t_token *token, t_obj *obj, int *j);
int		handle_export_args(char **av, t_obj *obj, int *count);
int		process_export_arg(char *arg, t_obj *obj);
void	swap_strings(char **s1, char **s2);
//signals
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	signal_handler(void);
void	signal_child(int sig);
//expand utlis 
char	*no_quotes(t_obj *obj, char **argv, int *i, int *j);
char	*do_quotes(t_obj *obj, char **argv, int *i, int *j);
char	*si_quotes(t_obj *obj, char **argv, int *i, int *j);
t_token	*create_token(char *str);
void	process_quotes(t_obj *obj, t_token *token, char **argv, int *ij);
void	process_token(t_obj *obj, t_token *token, int *j, char *str);
void	split_expanded(t_token *token);
char	*handle_special_chars(t_obj *obj, char *str);
char	*lookup_env_value(t_obj *obj, char *str);
void	write_input_line(t_obj *obj, char *str, int fd, char *stop);
void	process_child(t_obj *obj, char *s, int fd, char *stop);
char	*handle_dollar_quotes(char *input);
void	print_env_var(char *env);
void	print_env_name(char *env_value);
void	print_env_value(char *env_value, int i);
int		ft_process_wait_status(pid_t pid, int status, t_obj *obj);
void	handle_special_tokens(t_token **token_ptr);
//fail execute
void	handle_execution_error(t_obj *obj, char *path, char **env);
// cd utlis
void	update_env(t_obj *obj);
void	update_oldpwd(char **s1, char **s2);
// creat list utlis
int		argv_len(t_token *token);
void	ft_redirection(t_lexer **lexer, t_token **token);
void	export_error(char *arg, t_obj *obj);
int		is_valid_varname_char(char c, int is_first_char);
void	parse_echo_args(char ***str, int *id, int *no_new_line, int size);
#endif