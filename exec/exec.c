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

int builtin_executer(t_data *data, t_builtin type)
{
    int ret;

    ret = 0;
    if (type == FT_ENV)
        ret = ft_env(data);
    else if (type == FT_ECHO)
        ret = ft_echo(data->exec->args);
    else if (type == FT_CD)
        ret = ft_cd(data, data->exec->args);
    else if (type == FT_EXPORT)
        ret = ft_export(data, data->exec->args);
    else if (type == FT_PWD)
        ret = ft_pwd(data);
    else if (type == FT_UNSET)
        ret = ft_unset(data, data->exec->args);
    else if (type == FT_EXIT)
        ret = ft_exit(data, data->exec->args);
    data->status = ret;
    printf("\n\n STATUS = %d\n\n", data->status);
    return (ret);
}
/*
int executer_handler(t_data *data, int stdout_cpy)
{
    int i;
    int number_of_child_processes;

    i = 0;
    number_of_child_processes = data->exec_size;
    while (i < number_of_child_processes)
    {
        data->exec[i].path = path_parser(data, data->exec[i]);

    }
}
*/
int executer(t_data *data)
{
    //int stdin_copy;
    //int stdout_copy;

    if (data->exec[0].builtin != 0 && data->exec_size == 1)
        if (builtin_executer(data, data->exec[0].builtin) == -1)
            return (-1);
    //stdin_copy = dup(STDIN_FILENO);
    //stdout_copy = dup(STDOUT_FILENO);
    //executer_handler(data, stdout_copy);
    return (0);
}