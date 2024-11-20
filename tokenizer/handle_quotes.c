/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:34 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/17 17:07:35 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	handle_dquotes(t_token **tokens, char *input, int *i)
{
	int		start;

	*i = *i + 1;
	start = *i;
	while (input[*i] != '\0' && input[*i] != '"')
		(*i)++;
	if (add_token_to_list(tokens, DQUOTE, ft_substr(input, start, *i - start)) == -1) //watch out if substr returns NULL
		return (-1);
    (*i)++;
	return (0);
}

int	handle_quotes(t_token **tokens, char *input, int *i)
{
	int		start;

	*i = *i + 1;
	start = *i;
	while (input[*i] != '\0' && input[*i] != '\'')
		(*i)++;
	if (add_token_to_list(tokens, QUOTE, ft_substr(input, start, *i - start)) == -1) //watch out if substr returns NULL
		return (-1);
    (*i)++;
	return (0);
}

int	handle_word(t_token **tokens, char *input, int *i)
{
	int		start;

	start = *i;
	while (input[*i] != '\0' && strchr("><| '\"", input[*i]) == NULL)
		(*i)++;
	if (add_token_to_list(tokens, WORD, ft_substr(input, start, *i - start)) == -1) //watch out if substr returns null
		return (-1);
	return (0);
}
