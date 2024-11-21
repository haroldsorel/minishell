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

int file_parser(t_data *data, t_token *token, t_exec *exec)
{
    int	fd;

	fd = -1;
	//if (exec->in_file == -1 || exec->out_file == -1)
	//	return (-1); //understand why this guy told me this
	if (token->type == INFILE)
		fd = open(token->value, O_RDONLY);
	else if (token->type == OUTFILE)
		fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	else if (token->type == APPEND)
		fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 00777);
	//if (fd == -1) //to do
	if (fd == -1)
		data->status = 1;
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
