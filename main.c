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
    char    *user_input;

    while(1)
    {
        user_input = get_prompt(data);
        data->input = readline(user_input);
        free(user_input);
        if(data->input == NULL)
            return (-1);//to do
        printf("%s\n", data->input);
        //if (syntax_checker(data) == NULL)
         //   return (-1);
        //if (tokenizer(data) == NULL)
         //   return (-1); //to do
        //if (expander(data) == NULL)
         //   return (-1); //to do
        //if (parser(data) == NULL)
         //   return (-1); //to do
        //if (executer(data) == NULL)
         //   return (-1); //to do
        //free_all(data);
        //add_history(data->input);
    }
    system("leaks minishell");
    return (0);
}


int main(int argc, char **argv, char **env)
{
    t_data  data;

    (void)argc;
    (void)argv;
    init_all(&data, env); //env has to be modified it is just duplicated now
    minishell_launcher(&data);
    return (1);
    }

