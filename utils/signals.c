/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:22 by ababdoul          #+#    #+#             */
/*   Updated: 2025/05/15 12:07:58 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_special_char(void)
{
	struct termios term;
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void	heredoc_signal(int sig)
{
	(void)sig;
	get_signal = 1;
	write(1, "\n", 1);
	exit(1);
}

void	sigint_handler(int sig)
{
	get_signal = sig;
	if (waitpid(-1, &sig, WNOHANG) == 0)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	get_signal = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
