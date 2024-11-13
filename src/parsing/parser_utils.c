/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:48:39 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/13 14:48:40 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bin_node  *new_bin_node(t_token_type type)
{
    t_bin_node  *new_node;

    new_node = malloc(sizeof(t_bin_node));
    if (new_node == NULL)
        return (NULL);
    new_node->type = type;
    new_node->args = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}

/*
void    free_bin(t_bin_node)
{

}
*/