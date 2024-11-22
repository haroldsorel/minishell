/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:49:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:49:08 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int str_to_uint8(char *str)
{
    int64_t int64_res;
    int     neg;
    int     i;
    int     len;
    
    int64_res = 0;
    neg = 1;
    i = 0;
    len = 0;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        i++;
        neg = -1;
    }
    while (str[i] != '\0' && len < 19)
    {
        if (int64_res > (INT64_MAX - (str[i] - '0')) / 10)
            break ;
        int64_res = int64_res * 10 + (str[i] - '0');
        i++;
        len++;
    }
    return ((int)((int64_res * neg) % 256));
}

int valid_argument(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\0')
        return (0);
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i] != '\0')
    {
        if (ft_isdigit(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int ft_exit(t_data *data, char **args)
{
    int exit_code;

    exit_code = data->status;
    if (args[1] != NULL && args[2] != NULL)
    {
        write(1, "Exit: Too Many Arguments\n", 25);
        return (0); //should not exit the whole programme
    }
    if (args[1] == NULL || valid_argument(args[1]) == 0)
    {
        //free everything
        //exit(exit_code); //do i exit anyway?
        return (0);   
    }
    //free everything
    exit_code = str_to_uint8(args[1]);
    if (exit_code < 0)
        exit_code = exit_code + 256;
    printf("EXITCODE : %d\n", exit_code); //PRINTF TAKE OFF
    //exit(str_to_uint8(args[1]));
    return (0);
}
