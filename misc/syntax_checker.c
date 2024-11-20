/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:45:57 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/20 14:46:09 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int quotes_checker(char *input)
{
    int i;
    int is_quote;

    i = 0;
    while (input[i] != '\0')
    {
        is_quote = quotes_skipper(input, &i);
        if (is_quote == -1)
            return (-1);
        if (is_quote == 0)
            i++;
    }
    return (0);
}


int pipe_checker(char *input)
{
    int i;

    i = 0;
    while (input[i] != '\0')
    {
        while (input[i] != '\0' && input[i] == ' ')
            i++;
        if (ft_strchr("><|", input[i]) != NULL)
            return (-1);
        while (input[i] != '\0' && input[i] != '|')
        {
            if (quotes_skipper(input, &i) == 0)
                i++;
        }
        if (input[i] == '|' && input[i + 1] == '\0')
            return (-1);
        if (input[i] == '|')
            i++;
    }
    return (0);
}

int redir_checker(char *input)
{
    int i;

    i = 0;
    while (input[i] != '\0' && input[i] != '|')
    {
        if (quotes_skipper(input, &i) == 0)
            i++;
        if (input[i] == '>' || input[i] == '<')
        {
            i++;
            if (input[i] == input[i - 1])
                i++;
            if (input[i] == '\0')
                return (-1);
            while (input[i] != '\0' && input[i] == ' ')
                i++;
            if (ft_strchr("><|", input[i]) != NULL)
                return (-1);
        }
    }
    return (0);
}

int syntax_checker(char *input)
{
    if (input == NULL)
        return (-1);
    if (quotes_checker(input) == -1)
        return (syntax_error_handler("Quote Error\n"));
    if (pipe_checker(input) == -1)
        return (syntax_error_handler("Pipe Error\n"));
    if (redir_checker(input) == -1)
        return (syntax_error_handler("Redirection Error\n"));
    return (0);
}
