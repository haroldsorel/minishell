/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenater.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:51:02 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/19 13:51:04 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int concatenate_quote(t_token *token)
{
    t_token *tmp;

    tmp = NULL;
}

int concatenate_word(t_token *token) //check if prev is a file aswell but do that later
{
    t_token *tmp;

    tmp = NULL;
    if (token->prev == NULL)
        return (0);
    if ((token->prev->value)[ft_strlen(token->prev->value) - 1])
    
}

int concatenater(t_token **tokens)
{
    t_token *current;

    current = *tokens; //verify for NULL
    while (current != NULL)
    {
        if (current->type == WORD)
            concatenate_word(current);
        else if (current->type == QUOTE || current->type == DQUOTE)
            concatenate_quote(current);
        current->next;
    }
}

