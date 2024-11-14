/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:48:32 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/13 14:48:33 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bin_node	*parse_command(t_token **tokens)
{
	t_bin_node		*command_node;
	int				arg_count;

	command_node = new_bin_node(TOKEN_WORD);
    if (command_node == NULL)
        return (NULL); //follow up this return 
	arg_count = count_command_arguments(*tokens);
	command_node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!command_node->args)
		return (NULL);
	fill_command_arguments(command_node, tokens, arg_count);
	return (command_node);
}

t_bin_node	*create_file_node(t_token *token)
{
	t_bin_node			*node;

	node = malloc(sizeof(t_bin_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

t_bin_node	*redirection(t_token **tokens)
{
	t_token		*temp;
	t_bin_node	*redirect_node;
	t_token		*next_token;

	if (!*tokens)
		return (NULL);
	temp = *tokens;
	if ((*tokens)->type >= TOKEN_REDIR_IN
		&& (*tokens)->type <= TOKEN_REDIR_HEREDOC)
		return (create_and_link_redirection(tokens, temp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= TOKEN_REDIR_IN
			&& (*tokens)->next->type <= TOKEN_REDIR_HEREDOC)
		{
			redirect_node = new_bin_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = redirection(&temp);
			redirect_node->right = create_file_node((next_token->next));
			return (free(next_token->value), free(next_token), redirect_node);
		}
		*tokens = next_token;
	}
	return (parse_command(&temp));
}

t_bin_node	*pipeline(t_token **tokens)
{
	t_token		*tmp;
	t_token		*next_token;
	t_bin_node	*pipe_node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == TOKEN_PIPE)
		{
			pipe_node = new_bin_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = redirection(&tmp);
			pipe_node->right = pipeline(&(next_token->next));
			free(next_token->value);
			free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (redirection(&tmp));
}

t_bin_node  *parser(t_token **tokens)
{
    if (tokens == NULL || *tokens == NULL)
        return (NULL);
    return(pipeline(tokens));
}


