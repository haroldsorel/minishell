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
void    print_tokens(t_token *tokens);

int minishell_launcher(t_data *data)
{
    while(1)
    {
        if (prompt_launcher(data) == NULL) //mallocs and free user input next
            return (-1);
        //if (syntax_checker(data) == NULL) //no mallocs
          //  return (-1);
        //lexer(data, &(data->input)); //== NULL) //mallocs
        if (tokenizer(data, data->input) == -1)
            return (-1); //data to be freed
        print_tokens(data->tokens);
         //   return (-1); //to do
        if (expander(data) == -1)
            return (-1); //to do
        printf("AFTER EXPANDER\n");
        print_tokens(data->tokens);
        //if (parser(data) == NULL)
         //   return (-1); //to do
        //if (executer(data) == NULL)
         //   return (-1); //to do
        //add_history(data->input);
        //free_all(data);
    }
    return (0);
}

void    print_tokens(t_token *tokens)
{
    t_token *current;

    if (tokens == NULL)
        return ;
    current = tokens;
    while (current != NULL)
    {
        printf("%d:%s\n", current->type, current->value);
        current = current->next;
    }
}

int main(int argc, char **argv, char **env)
{
    t_data  data;

    (void)argc;
    (void)argv;
    init_all(&data, env); //env has to be modified it is just duplicated now and there is a malloc
    if (minishell_launcher(&data) == -1)
    {
        // to do
        return (1);
    }
    //free env mallocs
    //free
    return (1);
    }

