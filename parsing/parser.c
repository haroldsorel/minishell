/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:44:38 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/18 13:44:39 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int fill_one_command(t_data *data, t_token **tokens, t_exec *exec)
{
    t_token *current;

    current = *tokens;
    while (current != NULL && current->type != PIPE)
    {
        if (current->type == INFILE || current->type == OUTFILE
            || current->type == APPEND)
            file_parser(data, current, exec);
        //else if (current->type == HEREDOC)
		//	heredoc_parser(data, current, i);
		//else
		//	args_parser(data, current, i);
		//if (g_signal == SIGINT)
		//	return ;
		current = current->next;
    }
    *tokens = current;
    return (0);
}

int fill_commands(t_data *data, t_token **tokens)
{
    int i;

    i = 0;
    while (i < data->exec_size)
    {
        fill_one_command(data, tokens, &(data->exec[i]));
        i++;
    }
    return (0);
}

int init_exec(t_data *data)
{
    int i;

    i = 0;
    data->exec_size = count_pipes(&(data->tokens)) + 1;
    data->exec = malloc((data->exec_size) * sizeof(t_exec));
    if (data->exec == NULL)
        return (-1);
    while (i < data->exec_size)
    {
        data->exec[i].in_file = 0;
        data->exec[i].out_file = 1;
        data->exec[i].args = NULL;
        data->exec[i].path = NULL;
        i++;
    }
    return (0);
}

int parser(t_data *data)
{
    if (init_exec(data) == -1)
        return (-1);
    if (fill_commands(data, &(data->tokens)) == -1)
        return (-1);
    print_commands(data, data->exec);
    return (0);
}