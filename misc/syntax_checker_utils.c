/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:12:06 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/20 22:12:16 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int syntax_error_handler(char *str)
{
    printf("Syntax Error : %s\n", str); //PRINTF REPLACE  and just put str
    return (-1);
}

int quotes_skipper(char *input, int *i)
{
    if (input[*i] == '"')
    {
        (*i)++;
        while (input[*i] != '"')
        {
            if (input[*i] == '\0')
                return (-1);
            (*i)++;
        }
        (*i)++;
        return (1);
    }
    if (input[*i] == '\'')
    {
        (*i)++;
        while (input[*i] != '\'')
        {
            if (input[*i] == '\0')
                return (-1);
            (*i)++;
        }
        (*i)++;
        return (1);
    }
    return (0);
}