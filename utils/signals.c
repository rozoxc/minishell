/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:22 by ababdoul          #+#    #+#             */
/*   Updated: 2025/04/24 13:01:04 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void hide_ctrl_characters()
{
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void sigint_handler(int sig)
{
	(void)sig; // this canst for pass the error "unused parameter"
	write(STDOUT_FILENO, "\n", 1);  // Print a newline
	rl_replace_line("", 0);         // Clear the line buffer
	rl_on_new_line();               // Move to the new line
	rl_redisplay();                 // Display the prompt
}
void sigquit_handler(int sig)
{
    (void)sig;
    // printf("zbi");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void signal_handler()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}

// void setup_execution_signals(void)
// {
//     struct sigaction sa;

//     // Restore default SIGQUIT behavior (core dump)
//     sa.sa_handler = SIG_DFL;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sigaction(SIGQUIT, &sa, NULL);

//     // Keep custom SIGINT
//     sa.sa_handler = SIG_DFL;  // Or could use different handler
//     sigaction(SIGINT, &sa, NULL);
// }
