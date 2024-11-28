/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:19:19 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/16 17:19:20 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int minishell_launcher(t_data *data)
{
    while(1)
    {
        if (prompt_launcher(data) == NULL)
            return (exit_minishell_crash(data, USER_INPUT), -1);
        if (syntax_checker(data->input) == -1)
        {
            free(data->input);
            continue ;
        }
        if (tokenizer(data, data->input) == -1)
            return (exit_minishell_crash(data, TOKENIZATION), -1);
        if (parser(data) == -1)
            return(exit_minishell_crash(data, PARSING), -1);
        if (executer(data) == -1)
            return (exit_minishell_crash(data, EXECUTION), -1);
        free_all(data);
        return (0);
    }
    return (0);
}

int main(int argc, char **argv, char **env)
{
    t_data  data;

    (void)argc;
    (void)argv;
    init_all(&data, env); //env has to be modified it is just duplicated now and there is a malloc
    if (minishell_launcher(&data) == -1)
        return (1);
    return (0);
}

