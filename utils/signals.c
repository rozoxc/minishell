/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:22 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/19 10:28:39 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_special_char(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	signal_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	sigint_handler(int sig)
{
	g_signal = sig;
	if (waitpid(-1, &sig, WNOHANG) == 0)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	g_signal = sig;
	if (waitpid(-1, &sig, WNOHANG) == 0)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(void)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
}
