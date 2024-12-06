/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:45:20 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/16 23:45:21 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	handle_special_chars(t_token **tokens, char *input, int *i)
{
	int	flag;

	flag = 0;
	if (input[*i] == '|')
		flag = handle_pipe(tokens, i);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		flag = handle_append(tokens, input, i);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		flag = handle_heredoc(tokens, input, i);
	else if (input[*i] == '>')
		flag = handle_outfile(tokens, input, i);
	else if (input[*i] == '<')
		flag = handle_infile(tokens, input, i);
	return (flag);
}

static int	tokenizer_helper(t_token **tokens, char c, char *input, int *i)
{
	int	flag;

	flag = 0;
	if (ft_strchr("><|", c) != NULL)
		flag = handle_special_chars(tokens, input, i);
	else if (c == '\'')
		flag = handle_quotes(tokens, input, i);
	else if (c == '"')
		flag = handle_dquotes(tokens, input, i);
	else
		flag = handle_word(tokens, input, i);
	if (flag == -1)
		return (-1);
	return (flag);
}

int	tokenizer(t_data *data, char *input)
{
	t_token	*tokens;
	int		i;
	int		flag;

	tokens = NULL;
	i = 0;
	flag = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ')
		{
			while (input[i] == ' ')
				i++;
			flag = add_token_to_list(&tokens, FT_SPACE, ft_strdup(" "));
		}
		flag = tokenizer_helper(&tokens, input[i], input, &i);
	}
	data->tokens = tokens;
	if (expander(data) == -1 || concatenater(&(data->tokens)) == -1)
		return (-1);
	return (flag);
}
