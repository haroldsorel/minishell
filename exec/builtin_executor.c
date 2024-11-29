/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:03:19 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/27 19:03:20 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	builtin_executer(t_data *data, t_exec *exec, t_builtin type)
{
	int	ret;

	ret = 0;
	if (type == FT_ENV)
		ret = ft_env(data);
	else if (type == FT_ECHO)
		ret = ft_echo(exec->args);
	else if (type == FT_CD)
		ret = ft_cd(data, exec->args);
	else if (type == FT_EXPORT)
		ret = ft_export(data, exec->args);
	else if (type == FT_PWD)
		ret = ft_pwd(data);
	else if (type == FT_UNSET)
		ret = ft_unset(data, exec->args);
	else if (type == FT_EXIT)
		ret = ft_exit(data, exec->args);
	data->status = ret;
	return (ret);
}

int	builtin_handler(t_data *data, t_exec *exec, t_builtin type)
{
	int	stdin_cpy;
	int	stdout_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	if (type == FT_EXIT)
		ft_putstr_fd("exit\n", 1);
	if (exec->in_file > -1)
		dup2(exec->in_file, STDIN_FILENO);
	if (exec->out_file > 2)
		dup2(exec->out_file, STDOUT_FILENO);
	if (builtin_executer(data, exec, type) == -1)
		return (-1);
	dup2(stdin_cpy, STDIN_FILENO);
	dup2(stdout_cpy, STDOUT_FILENO);
	close(stdin_cpy);
	close(stdout_cpy);
	return (0);
}
