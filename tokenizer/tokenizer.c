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

void    print_tokens(t_token *tokens);

static int	pipe_checker(t_token *token)
{
	if (token != NULL && token->type == PIPE)
    {
        printf("Syntax Error : PIPE\n"); //watch out printf
		return (-1);
    }
	while (token && token->next)
	{
		if (token->type == PIPE && token->next->type == PIPE)
        {
            printf("Syntax Error : PIPE\n"); //watch out printf
            return (-1);
        }
		token = token->next;
	}
	if (token->type == PIPE)
    {
        printf("Syntax Error : PIPE\n"); //watch out printf
		return (-1);
    }
	return (0);
}

int handle_special_chars(t_token **tokens, char *input, int *i)
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

int	tokenizer(t_data *data, char *input)
{
	t_token	*tokens; //this step is not necessary just put data->tokens int the arguments
	int		i;
	int		flag;

	tokens = NULL; //idem
	i = 0;
	flag = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ')
		{
			while (input[i] == ' ')
				i++;
			flag = add_token_to_list(&tokens, SPACE, ft_strdup(" ")); //if strdup fails follow up
		}
		if (ft_strchr("><|", input[i]) != NULL)
			flag = handle_special_chars(&tokens, input, &i);
		else if (input[i] == '\'')
			flag = handle_quotes(&tokens, input, &i);
		else if (input[i] == '"')
			flag = handle_dquotes(&tokens, input, &i);
		else
			flag = handle_word(&tokens, input, &i);
		if (flag == -1)
			return (-1);
	}
	data->tokens = tokens; //idem
	if (expander(data) == -1)
		return (-1);
	if (concatenater(&tokens) == -1) //connect these together with || after testing 
		return (-1);
	if (pipe_checker(tokens) == -1)
		return (-1);
	return (0);
}
