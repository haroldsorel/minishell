/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:21:03 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:21:05 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	executer_handler(t_data *data, int stdout_cpy)
{
	int	i;
	int	number_of_child_processes;

	i = 0;
	number_of_child_processes = data->exec_size;
	while (i < number_of_child_processes)
	{
		pipe_executor(data, &(data->exec[i]), i, stdout_cpy);
		i++;
	}
	return (0);
}

static void	receive_sig(t_data *data)
{
	if (g_signal == SIGINT)
	{
		data->status = 130;
		g_signal = 0;
	}
	if (g_signal == SIGQUIT)
	{
		data->status = 131;
		g_signal = 0;
	}
}

static void	wait_for_child_processes_to_finish(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->exec_size)
	{
		wait(NULL);
		i++;
	}
}

int	executer(t_data *d)
{
	int	status;
	int	stdin_copy;
	int	stdout_copy;

	if (d->exec[0].builtin != 0 && d->exec_size == 1)
	{
		if (builtin_handler(d, &(d->exec[0]), d->exec[0].builtin) == -1)
			return (-1);
		return (0);
	}
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	executer_handler(d, stdout_copy);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	waitpid(d->pid, &status, 0);
	d->status = WEXITSTATUS(status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_interrupt);
	disable_signal_print();
	receive_sig(d);
	wait_for_child_processes_to_finish(d);
	return (0);
}
