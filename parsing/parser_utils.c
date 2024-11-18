/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:45:00 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/18 13:45:02 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int count_pipes(t_token **tokens)
{
    t_token *current;
    int     count;

    count = 0;
    current = *tokens;
    while (current != NULL)
    {
        if (current->type == PIPE)
            count++;
        current = current->next;
    }
    return (count);
}