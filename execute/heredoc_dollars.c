/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:03:07 by hfalati           #+#    #+#             */
/*   Updated: 2025/05/08 16:03:40 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	copy_dollar_sequence(char *s, int read, int *write)
{
	int	start;
	int	run_len;
	int	to_keep;
	int	k;

	start = read;
	while (s[read] == '$')
		read++;
	run_len = read - start;
	to_keep = run_len - (run_len % 2);
	if (run_len == 1 && s[read] == '\0')
		to_keep++;
	k = 0;
	while (k < to_keep)
	{
		s[(*write)++] = '$';
		k++;
	}
	return (read);
}

void	adjust_dollars(char *s)
{
	int	read;
	int	write;

	read = 0;
	write = 0;
	while (s[read] != '\0')
	{
		if (s[read] == '$')
			read = copy_dollar_sequence(s, read, &write);
		else
			s[write++] = s[read++];
	}
	s[write] = '\0';
}
