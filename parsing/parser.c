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
/*
int init_args(t_data *data, t_token *tokens)
{
    int i;

    i = 0;
    return (i);
}
*/
int init_exec(t_data *data)
{
    int i;

    i = 0;
    data->exec_size = count_pipes(&(data->tokens));
    data->exec = malloc((data->exec_size + 1) * sizeof(t_exec));
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
    //if (init_args(data, data->tokens) == -1)
    //    return (-1);
    return (0);
}