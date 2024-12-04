/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/17 17:07:08 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	handle_pipe(t_token **tokens, int *i)
{
	if (add_token_to_list(tokens, PIPE, ft_strdup("|")) == -1)
		return (-1);
	(*i)++;
	return (0);
}

int	handle_outfile(t_token **tokens, char *input, int *i)
{
	int	start;

	*i = *i + 1;
	while (input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		if (add_token_to_list(tokens, OUTFILE, extract_word_from_quote(input, i, input[*i])) == -1)
			return (-1);
		return (0);
	}
	while (input[*i] != '\0' && strchr("><| '\"", input[*i]) == NULL)
		(*i)++;
	if (add_token_to_list(tokens, OUTFILE, ft_substr(input, start, *i - start)) == -1)
		return (-1);
	return (0);
}

int	handle_infile(t_token **tokens, char *input, int *i)
{
	int	start;

	*i = *i + 1;
	while (input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		if (add_token_to_list(tokens, INFILE, extract_word_from_quote(input, i, input[*i])) == -1)
			return (-1);
		return (0);
	}
	while (input[*i] != '\0' && strchr("><| '\"", input[*i]) == NULL)
		(*i)++;
	if (add_token_to_list(tokens, INFILE, ft_substr(input, start, *i - start)) == -1)
		return (-1);
	return (0);
}

int	handle_heredoc(t_token **tokens, char *input, int *i)
{
	int	start;

	*i = *i + 2;
	while (input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '\'')
	{
		if (add_token_to_list(tokens, S_HEREDOC, extract_word_from_quote(input, i, input[*i])) == -1)
			return (-1);
		return (0);
	}
	if (input[*i] == '"')
	{
		if (add_token_to_list(tokens, S_HEREDOC, extract_word_from_quote(input, i, input[*i])) == -1)
			return (-1);
		return (0);
	}
	while (input[*i] != '\0' && strchr("><| '\"", input[*i]) == NULL)
		(*i)++;
	if (add_token_to_list(tokens, HEREDOC, ft_substr(input, start, *i - start)) == -1)
		return (-1);
	return (0);
}

int	handle_append(t_token **tokens, char *input, int *i)
{
	int	start;

	*i = *i + 2;
	while (input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		if (add_token_to_list(tokens, APPEND, extract_word_from_quote(input, i, input[*i])) == -1)
			return (-1);
		return (0);
	}
	while (input[*i] != '\0' && strchr("><| '\"", input[*i]) == NULL)
		(*i)++;
	if (add_token_to_list(tokens, APPEND, ft_substr(input, start, *i - start)) == -1)
		return (-1);
	return (0);
}
