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

void	builtin_executer(t_data *data, t_builtin type)
{
    if (type == FT_ENV)
        ft_env(data);
    else if (type == FT_ECHO)
        ft_echo(data->exec->args);
    //else if (type == FT_CD)
    //    ft_cd(data);
    //else if (type == FT_EXPORT)
     //   ft_export(data);
    else if (type == FT_PWD)
        ft_pwd(data);
    //else if (type == FT_UNSET)
    //    ft_unset(data);
    else if (type == FT_EXIT)
        ft_exit(data, data->exec->args);
   else
        printf("Command Not Found\n"); //PRINTF TAKE OFF
}

int executer(t_data *data)
{
    if (data->exec[0].builtin)
        builtin_executer(data, data->exec[0].builtin);
    return (0);

}