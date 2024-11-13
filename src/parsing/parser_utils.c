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
void    free_bin(t_bin_node *node)
{
    (void*)node;
    return ; //finish this
}
*/

t_bin_node	*create_and_link_redirection(t_token **tokens, t_token *tmp)
{
	t_bin_node	*redirect_node;

	redirect_node = new_bin_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = redirection(tokens);
	redirect_node->right = create_file_node(tmp->next);
	free(tmp->value);
	free(tmp);
	return (redirect_node);
}

int	count_command_arguments(t_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == TOKEN_WORD)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	fill_command_arguments(t_bin_node *command_node,
	t_token **tokens, int arg_count)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i < arg_count)
	{
		command_node->args[i] = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->value);
		free(tmp);
		i++;
	}
	command_node->args[arg_count] = NULL;
}
