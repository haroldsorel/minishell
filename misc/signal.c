/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:19:37 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/16 17:19:38 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <readline/readline.h>

void	sig_quit(int signal)
{
	write(2, "Quit: 3\n", 8);
	g_signal = signal;
}

void	enable_signal_print(void)
{
	struct termios	termios_new;

	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}

void	disable_signal_print(void)
{
	struct termios	termios_new;

	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}

void	sig_interrupt_exec(int signal)
{
	g_signal = signal;
	write(1, "\n", 1);
}

void	sig_interrupt(int signal)
{
	(void)signal;
	g_signal = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
