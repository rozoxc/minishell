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

// execution structs

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
t_token *main_parser(char *input);
t_token *lexer(char *input);
t_cmd *parse_tokens(t_token *tokens);

//utils functions
char	**ft_split(char *s, char c);
int ft_strcmp(char *s1, char *s2);
char *ft_strdup(char *str);
int ft_strlen(char *str);
#endif