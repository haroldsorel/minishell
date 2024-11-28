/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:08:40 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/17 01:08:42 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void    free_one_token(t_token *token)
{
    if (token == NULL)
        return ;
    free(token->value);
    free(token);
}

void    *free_array_of_pointers(char **array)
{
    int     i;

    i = 0;
    if (array == NULL)
        return (NULL);
    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
    return (NULL);
}

void    free_tokens(t_token **tokens)
{
    t_token *current;
    t_token *temp;

    if (tokens == NULL || *tokens == NULL)
        return ;
    current = *tokens;
    while (current != NULL)
    {
        temp = current->next;
        free_one_token(current);
        current = temp;
    }
    *tokens = NULL;
}

void    *free_commands(t_data *data)
{
    int i;

    i = 0;
    while (i < data->exec_size)
    {
        if (data->exec[i].path != NULL)
            free(data->exec[i].path);
        free_array_of_pointers(data->exec[i].args);
        i++;
    }
    free(data->exec);
    return (NULL);
}


void    exit_minishell_crash(t_data *data, t_steps step)
{
    ft_putstr_fd("System Error\n", 2);
    free_array_of_pointers(data->env);
    data->status = 1;
    if (step == TOKENIZATION)
        free(data->input);
    if (step == PARSING)
    {
        free(data->input);
        free_tokens(&(data->tokens));
    }
    if (step == EXECUTION)
    {
        free(data->input);
        free_tokens(&(data->tokens));
        free_commands(data);
    }
    exit_minishell(data);
}

void    free_all(t_data *data)
{
    free(data->input);
    free_tokens(&(data->tokens));
    free_commands(data);
    //close files
}

void    exit_minishell(t_data *data)
{
    free_all(data);
    free_array_of_pointers(data->env);
    rl_clear_history();
    printf("\n\nSTATUS : %d\n\n", data->status);
    system("leaks minishell");
    exit(data->status);
}