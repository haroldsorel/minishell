/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:21:16 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:21:18 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int handle_child(t_data *data, t_exec *exec, int *link)
{
    close(link[1]);
    close(link[0]);
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
    enable_signal_print();
    if (exec->in_file == -1 || exec->out_file == -1)
		exit (1);
	if (exec->builtin != 0)
	{
		builtin_handler(data, exec, exec->builtin);
		exit (data->status);
	}
	else if (execve(exec->path, exec->args, data->env) < 0)
		exit (data->status);
    return (0);
}

int handle_parent(t_exec *exec, int *link)
{
    signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_interrupt_exec);
	close(link[1]);
	if (exec->in_file <= 2)
		dup2(link[0], STDIN_FILENO);
	close(link[0]);
    return (0);
}

int pipe_executor(t_data *data, t_exec *exec, int index , int stdout_copy)
{
    int link[2];

    if (pipe(link) == -1)
        exit_minishell_crash(data);
    if (index < data->exec_size - 1)
        dup2(link[1], STDOUT_FILENO);
    else
        dup2(stdout_copy, STDOUT_FILENO);
    if (exec->in_file > 2)
        dup2(exec->in_file, STDIN_FILENO);    
    if (exec->out_file > 2)
        dup2(exec->out_file, STDOUT_FILENO);
    data->pid = fork();
    if (data->pid < 0)
        exit_minishell_crash(data);
    if (data->pid == 0)
        handle_child(data, exec, link);
    else
        handle_parent(exec, link);
    return (0);
}
