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

void	check_for_empty_token(t_token *token, t_token **head)
{
	t_token	*temp;

	temp = token;
	if ((token->value)[0] != '\0')
		return ;
	if (token->prev == NULL)
	{
		if (token->next == NULL)
			*head = NULL;
		else
		{
			*head = token->next;
			(*head)->prev = NULL;
		}
	}
	else
	{
		token->prev->next = token->next;
		if (token->next != NULL)
			token->next->prev = token->prev;
	}
	free_one_token(temp);
}

int	concatenate_word(t_token *current)
{
	char	*old_value;

	old_value = current->prev->value;
	current->prev->value = ft_strjoin(current->prev->value, current->value);
	free(old_value);
	if (current->prev->value == NULL)
		return (-1);
	current->prev->next = current->next;
	if (current->next != NULL)
		current->next->prev = current->prev;
	free_one_token(current);
	return (0);
}

void	delete_spaces(t_token **token)
{
	t_token	*current;
	t_token	*temp;

	temp = NULL;
	current = *token;
	while (current != NULL)
	{
		if (current->type == FT_SPACE)
		{
			temp = current->next;
			if (current->prev == NULL)
				*token = current->next;
			else
				current->prev->next = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free_one_token(current);
			current = temp;
		}
		else
			current = current->next;
	}
}

int	concatenater(t_token **tokens)
{
	t_token	*current;
	t_token	*temp;

	current = *tokens;
	while (current != NULL)
	{
		if (current->type == WORD || current->type == DQUOTE
			|| current->type == QUOTE)
		{
			if (current->prev != NULL && current->prev->type != FT_SPACE
				&& current->prev->type != PIPE)
			{
				temp = current->next;
				if (concatenate_word(current) == -1)
					return (-1);
				current = temp;
			}
			else
				current = current->next;
		}
		else
			current = current->next;
	}
	delete_spaces(tokens);
	return (0);
}
