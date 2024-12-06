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

static void	print_error(t_data *data, char *cmd)
{
	if (cmd != NULL)
	{
		data->status = 127;
		if ((cmd[0] == '/') || (cmd[0] == '.' && cmd[1] == '/'))
		{
			if (is_directory(cmd) == 1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd("is a directory: ", 2);
				data->status = 126;
			}
			if (access(cmd, F_OK) == -1)
				ft_putstr_fd("minishell: No such file or directory: ", 2);
			else if (access(cmd, X_OK) == -1)
			{
				ft_putendl_fd("minishell: Permission denied: ", 2);
				data->status = 126;
			}
		}
		else
			ft_putstr_fd("minishell: Command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
}

int	handle_child(t_data *data, t_exec *exec, int *link)
{
	close(link[1]);
	close(link[0]);
	enable_signal_print();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exec->in_file == -1 || exec->out_file == -1)
	{
		data->status = 1;
		return (0);
	}
	else if (exec->builtin != 0)
		builtin_handler(data, exec, exec->builtin);
	else if (exec->builtin == 0 && exec->path == NULL)
		print_error(data, exec->args[0]);
	else
		execve(exec->path, exec->args, data->env);
	return (0);
}

int	handle_parent(t_data *data, int *link, int index)
{
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_interrupt_exec);
	close(link[1]);
	if (index < (data->exec_size - 1) && data->exec[index + 1].in_file <= 2)
		dup2(link[0], STDIN_FILENO);
	close(link[0]);
	return (0);
}

int	pipe_executor(t_data *data, t_exec *exec, int index, int stdout_copy, int stdin_copy)
{
	int	link[2];

	if (pipe(link) == -1)
		exit_minishell_crash(data, EXECUTION);
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
		exit_minishell_crash(data, EXECUTION);
	if (data->pid == 0)
	{
		handle_child(data, exec, link);
		close(stdout_copy);
		close(stdin_copy);
		exit(data->status);
	}
	else
		handle_parent(data, link, index);
	return (0);
}
