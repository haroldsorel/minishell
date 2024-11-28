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

int print_tokens(t_token *tokens);

int fill_one_command(t_data *data, t_token **tokens, t_exec *exec)
{
    t_token *current;

    current = *tokens;
    if (file_parser(data, *tokens, exec) == -1)
        return (-1);
	if (heredoc_parser(data, current, exec) == -1)
       return (-1);
	if (args_parser(*tokens, exec) == -1)
        return (-1);
    parse_builtin(exec);
    if (path_parser(data, exec, exec->args[0]) == -1)
        return (-1);
    while (current != NULL && current->type != PIPE)
        current = current->next;
    if (current != NULL && current->type == PIPE)
        current = current->next;
    *tokens = current;
    return (0);
}

int fill_commands(t_data *data, t_token **tokens)
{
    int i;

    i = 0;
    while (i < data->exec_size)
    {
        if (fill_one_command(data, tokens, &(data->exec[i])) == -1)
            return (-1);
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
        data->exec[i].builtin = 0;
        i++;
    }
    return (0);
}

int parser(t_data *data)
{
    t_token *head;

    head = data->tokens;
    if (init_exec(data) == -1)
        return (-1);
    if (fill_commands(data, &(data->tokens)) == -1)
        return (-1);
    data->tokens = head;
    return (0);
}