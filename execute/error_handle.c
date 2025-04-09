#include "../includes/minishell.h"

int	determine_exit_code(t_obj *obj, int exit_code)
{
	obj->exit_code = exit_code;
	return (exit_code);
}

void	pipe_error(t_obj *obj, int pid)
{
    if (pid == -1)
    {
        ft_putstr_fd("minishell error : ", 2);
        perror("pipe error");
        exit(determine_exit_code(obj, 130));
    }
    return (pid);
}

int	fork_error(t_obj *obj, int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("fork error");
		exit(determine_exit_code(obj, 130));
	}
	return (pid);
}

int	dup_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("dup error");
		exit(determine_exit_code(obj, 130));
	}
	return (dup);
}

void	dup2_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("dup2 error");
		exit(determine_exit_code(obj, 130));
	}
}