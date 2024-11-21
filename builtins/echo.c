/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:48:48 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:48:49 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int  valid_flag(char *str)
{
    int i;

    if (str[0] == '\0' || str[0] != '-')
        return (0);
    i = 1;
    while (str[i] != '\0' && str[i] == 'n')
        i++;
    if (str[i] == '\0')
        return (1);
    return (0);
}

void    ft_echo(char **args)
{
    int i;
    int flag;

    i = 1;
    flag = 0;
    if (args[1] != NULL && valid_flag(args[1]) == 1)
        flag = 1;
    while (args[i] != NULL && valid_flag(args[i]) == 1)
        i++;
    while (args[i] != NULL)
    {
        printf("%s", args[i]); //PRINTF CHANGE!!!
        if (args[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (flag == 0)
        printf("\n"); //PRINTF CHANGE!!!
}