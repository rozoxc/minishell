#include "../includes/minishell.h"

int	set_red_input(t_lexer *red)
{
	int		fd;

	fd = open(red->str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell Err, infile, No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("Minishell Error: redirection\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	set_redirections(t_cmd *cmd)
{
	t_lexer	*red_temp;

	if (cmd == NULL)
		return (0);
	red_temp = cmd->lexer;
	while (red_temp)
	{
		if (red_temp->i == INPUT || red_temp->i == HEREDOC)
		{
			if (set_red_input(red_temp) == EXIT_FAILURE)
				return (Q_ERROR);
		}
	}
	return (0);
}