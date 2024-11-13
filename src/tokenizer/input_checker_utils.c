/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:33:00 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/13 17:33:01 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == 34)
		(*d_q_count)++;
	else if (c == 39)
		(*s_q_count)++;
}

const char	*skip_spaces(const char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

int	is_invalid_operator(const char **input)
{
	const char	*operator_start;

	operator_start = *input;
	(*input)++;
	if (*operator_start == **input)
		(*input)++;
	*input = skip_spaces(*input);
	if (**input == '\0' || **input == '>'
		|| **input == '<' || **input == '|')
		return (1);
	return (0);
}