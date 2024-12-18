/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:42:10 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/20 23:42:11 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	file_error(char *filename)
{
	if (is_directory(filename) == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else
	{
		if (access(filename, F_OK) == -1)
			ft_putstr_fd("minishell: no such file or directory: ", 2);
		else if (access(filename, X_OK) == -1)
			ft_putstr_fd("minishell: permission denied: ", 2);
		ft_putendl_fd(filename, 2);
	}
}

static int	file_handler(t_token *token, t_exec *exec)
{
	int	fd;

	fd = -1;
	if (exec->in_file == -1 || exec->out_file == -1)
		return (0);
	if (token->type == INFILE)
		fd = open(token->value, O_RDONLY);
	else if (token->type == OUTFILE)
		fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	else if (token->type == APPEND)
		fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 00777);
	if (fd == -1)
		file_error(token->value);
	if (token->type == INFILE && exec->in_file > 2)
		close(exec->in_file);
	else if (token->type != INFILE && exec->out_file > 2)
		close(exec->out_file);
	if (token->type == INFILE)
		exec->in_file = fd;
	else if (token->type == OUTFILE || token->type == APPEND)
		exec->out_file = fd;
	else
		close(fd);
	return (0);
}

int	file_parser(t_token *current, t_exec *exec)
{
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == INFILE || current->type == OUTFILE
			|| current->type == APPEND)
			if (file_handler(current, exec) == -1)
				return (-1);
		current = current->next;
	}
	return (0);
}
