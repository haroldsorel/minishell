/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:51:08 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/18 13:51:09 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_insert(char *old_str, char *new_str, int i, int j)
{
	char	*part_1;
	char	*part_2;
	char	*tmp;

	part_1 = ft_substr(old_str, 0, i);
	part_2 = ft_substr(old_str, j, ft_strlen(old_str + j));
	if (!part_1 || !part_2)
		return (free(part_1), free(part_2), NULL);
	if (!new_str)
	{
		tmp = ft_strjoin(part_1, part_2);
		return (free(part_1), free(part_2), tmp);
	}
	tmp = ft_strjoin(part_1, new_str);
	free(part_1);
	if (!tmp)
		return (free(part_2), NULL);
	part_1 = ft_strjoin(tmp, part_2);
	free(part_2);
	free(tmp);
	if (!part_1)
		return (NULL);
	return (part_1);
}

static int	handle_special_variable(t_data *data, t_token *token, int *i)
{
	char	*temp;
	char	*status;
	int		j;

	j = *i + 1;
	if ((token->value)[0] == '~' && (token->value)[1] == '\0')
	{
		if (get_env_variable(data->env, "HOME") != NULL)
			status = ft_strdup(get_env_variable(data->env, "HOME"));
		else
			status = ft_strdup("~");
	}
	else
	{
		status = ft_itoa(data->status);
		j++;
	}
	temp = ft_insert(token->value, status, *i, j);
	free(token->value);
	*i = *i + ft_strlen(status);
	free(status);
	if (temp == NULL)
		return (-1);
	token->value = temp;
	return (0);
}

static int	handle_env_variable(t_data *data, t_token *token
	, char *word, int *i)
{
	int		j;
	char	*var;
	char	*value;
	char	*new_word;

	j = *i;
	j++;
	while (word[j] != '\0' && (ft_isalnum(word[j]) || word[j] == '_'))
		j++;
	var = ft_substr(word, *i + 1, j - (*i + 1));
	if (var == NULL)
		return (-1);
	value = get_env_variable(data->env, var);
	free(var);
	new_word = ft_insert(word, value, *i, j);
	(*i) = *i + ft_strlen(value);
	free(word);
	if (new_word == NULL)
		return (-1);
	token->value = new_word;
	return (0);
}

static int	handle_expander(t_data *data, t_token *token)
{
	int	i;

	i = 0;
	while ((token->value)[i] != '\0')
	{
		if (((token->value)[0] == '~' && (token->value)[1] == '\0'
			&& token->type == WORD)
			|| ((token->value)[i] == '$' && (token->value)[i + 1] == '?'))
		{
			if (handle_special_variable(data, token, &i) == -1)
				return (-1);
		}
		else if (token->value[i] == '$' && (!ft_isalnum(token->value[i + 1])
				|| token->value[i + 1] == '\0'))
			i++;
		else if ((token->value)[i] == '$')
		{
			if (handle_env_variable(data, token, token->value, &i) == -1)
				return (-1);
		}
		else
			i++;
	}
	check_for_empty_token(token, &(data->tokens));
	return (0);
}

int	expander(t_data *data)
{
	t_token	*t;
	t_token	*next;

	t = data->tokens;
	while (t != NULL)
	{
		next = t->next;
		if (t->type == WORD || t->type == DQUOTE || t->type == INFILE
			|| t->type == OUTFILE || t->type == APPEND)
		{
			if ((t->value)[0] == '\0')
			{
				t = next;
				continue ;
			}
			if (handle_expander(data, t) == -1)
				return (-1);
		}
		t = next;
	}
	return (0);
}
