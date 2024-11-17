/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:47:42 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/17 01:47:44 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_token  *new_token(t_token_type type, char *value)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (new == NULL)
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
    new->value = value;
    new->type = type;
    return (new);
}
int    add_token_to_list(t_token **tokens, t_token_type type, char *value)
{
    t_token *new;
    t_token *current;

    current = *tokens;
    new = new_token(type, value);
    if (new == NULL)
    {
        //free token list
        return (-1);
    }
    if (*tokens == NULL)
    {
        *tokens = new;
        return (0);
    }

    while (current->next != NULL)
        current = current->next;
    current->next = new;
    new->prev = current;
    return (0);
}

char    *extract_word_from_quote(char *line, int *i, char quote)
{
    char    *extracted_word;
    int     start;

    (*i)++;
    extracted_word = NULL;
    start = *i;
    while (line[*i] != '\0' && line[*i] != quote)
        (*i)++;
    extracted_word = ft_substr(line, start, *i - start);
    if (extracted_word == NULL)
        return (NULL);
    (*i)++;
    return (extracted_word);
}