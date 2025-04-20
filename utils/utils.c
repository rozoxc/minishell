#include "../includes/minishell.h"

void	skip_space(char **str)
{
	while (*(*str) == ' ' || *(*str) == '\t' \
		|| *(*str) == '\r' || *(*str) == '\v' || *(*str) == '\f')
		(*str)++;
}

char	set_char(char **str, char c)
{
	if (*(*str) == c)
		return (0);
	else
		return (*(*str));
}

int	check_sep(char **str, char c)
{
	if (c != 0)
		return (0);
	else if ((*(*str) == '>' || *(*str) == '<'))
	{
		if (*(*str + 1) == *(*str))
			return (0);
		return (1);
	}
	else if ((*(*str) == ' ' || *(*str) == '|'))
		return (1);
	else if ((*(*str + 1) == ' ' || *(*str + 1) == '|' \
			|| *(*str + 1) == '>' || *(*str + 1) == '<'))
		return (1);
	return (0);
}