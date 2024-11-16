/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:51:04 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/06 18:51:06 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*handle_special_chars(char **input, t_token **tokens)
{
    t_token *new;

    new = NULL;
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			new = new_token(TOKEN_REDIR_APPEND, ">>");
			(*input)++;
		}
		else
			new = new_token(TOKEN_REDIR_OUT, ">");
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			new = new_token(TOKEN_REDIR_HEREDOC, "<<");
			(*input)++;
		}
		else
			new = new_token(TOKEN_REDIR_IN, "<");
	}
	else if (**input == '|')
		new = new_token(TOKEN_PIPE, "|");
	(*input)++;
    if (new == NULL)
        return (NULL);
    add_token_to_list(tokens, new);
    return (new);
}

void	*handle_word(char **input, t_token **tokens)
{
	char	*start;
	int		in_quote;
	char	quote_char;

	start = *input;
	in_quote = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t\n><|", **input))
			break ;
		(*input)++;
	}
	add_word_token_if_valid(&start, input, tokens);
    return (start);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	while (*input)
	{
		while (*input && ft_strchr(" \t\n", *input))
			input++;
		if (ft_strchr("><|", *input))
        {
			if (handle_special_chars(&input, &tokens) == NULL)
                return (free_tokens(tokens));
        }
		else
        {
			if (handle_word(&input, &tokens) == NULL)
            {
                free(tokens);
                return (free_tokens(tokens));
            }
        }
	}
	return (tokens);
}
