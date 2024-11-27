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
    free(array); //if was malloced
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
/*
void    *free_commands(t_exec *exec)
{

}
*/

void    exit_minishell(t_data *data)
{
    free_array_of_pointers(data->env);
    //free_commands(data->exec);
    //close all files
    rl_clear_history();
    printf("\n\nSTATUS : %d\n\n", data->status);
    exit(data->status);
}