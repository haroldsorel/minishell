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
        free(current->value);
        free(current);
        current = temp;
    }
    *tokens = NULL;
}

