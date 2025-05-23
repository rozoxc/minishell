/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis1_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:23:42 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/24 23:55:38 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env_entries(t_env *env)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**array;
	int		count;
	int		i;

	count = count_env_entries(env);
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		array[i] = ft_strdup(current->value);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			return (free(array), NULL);
		}
		current = current->next;
		i++;
	}
	array[count] = NULL;
	return (array);
}

void	cleanup_execution(t_obj *obj, int std_in, int std_out, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	dup2_error(obj, dup2(std_in, STDIN_FILENO));
	dup2_error(obj, dup2(std_out, STDOUT_FILENO));
	close_fds(std_in, std_out);
}

int	is_heredoc(t_cmd *cmd)
{
	t_lexer	*lexer;

	lexer = NULL;
	while (cmd)
	{
		lexer = cmd->lexer;
		while (lexer)
		{
			if (lexer->i == HEREDOC)
				return (1);
			lexer = lexer->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	setup_execution(t_obj *obj, int *std_in, int *std_out, char ***env)
{
	*env = env_to_array(obj->env);
	*std_in = dup_error(obj, dup(STDIN_FILENO));
	*std_out = dup_error(obj, dup(STDOUT_FILENO));
	if (ft_heredoc(obj) == FAILURE)
	{
		while (obj->cmd->lexer)
		{
			if (obj->cmd->lexer->i == HEREDOC)
			{
				free(obj->cmd->lexer->str);
				free(obj->cmd->lexer);
				close(obj->cmd->lexer->fd);
			}
			else
			{
				free(obj->cmd->lexer->str);
				free(obj->cmd->lexer);
			}
			obj->cmd->lexer = obj->cmd->lexer->next;
		}
		cleanup_execution(obj, *std_in, *std_out, *env);
		return (determine_exit_code(obj, 1), 1);
	}
	return (0);
}
