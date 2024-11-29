/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:08:57 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 00:09:08 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *current)
{
	int	count;

	count = 0;
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == WORD || current->type == DQUOTE
			|| current->type == QUOTE)
			count++;
		current = current->next;
	}
	return (count);
}

int	args_parser(t_data *data, t_token *token, t_exec *exec)
{
	int	size;
	int	i;

	size = count_args(token);
	i = 0;
	exec->args = malloc((size + 1) * sizeof(char *));
	if (exec->args == NULL)
		exit_minishell_crash(data, PARSING);
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == WORD || token->type == QUOTE
			|| token->type == DQUOTE)
		{
			exec->args[i] = ft_strdup(token->value);
			if (exec->args[i] == NULL)
			{
				free_array_of_pointers(exec->args);
				exit_minishell_crash(data, PARSING);
			}
			i++;
		}
		token = token->next;
	}
	exec->args[i] = NULL;
	return (0);
}
