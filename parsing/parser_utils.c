/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:45:00 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/18 13:45:02 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*heredoc_handle_special_variable(t_data *data, char *word, int *i)
{
	char	*temp;

	if (word[*i + 1] == '?')
		temp = ft_itoa(data->status);
	else
		temp = ft_itoa(getpid());
	if (temp == NULL)
		exit_minishell_crash(data, PARSING);
	temp = ft_insert(word, temp, *i, *i + 2);
	free(word);
	if (temp == NULL)
		exit_minishell_crash(data, PARSING);
	return (temp);
}

char	*heredoc_handle_env_variable(t_data *data, char *word, int *i)
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
		exit_minishell_crash(data, PARSING);
	value = get_env_variable(data->env, var);
	free(var);
	new_word = ft_insert(word, value, *i, j);
	(*i) = *i + ft_strlen(value);
	free(word);
	if (new_word == NULL)
		exit_minishell_crash(data, PARSING);
	return (new_word);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	parse_builtin(t_exec *exec)
{
	if (!ft_strcmp(exec->args[0], "echo"))
		exec->builtin = FT_ECHO;
	else if (!ft_strcmp(exec->args[0], "cd"))
		exec->builtin = FT_CD;
	else if (!ft_strcmp(exec->args[0], "env"))
		exec->builtin = FT_ENV;
	else if (!ft_strcmp(exec->args[0], "export"))
		exec->builtin = FT_EXPORT;
	else if (!ft_strcmp(exec->args[0], "pwd"))
		exec->builtin = FT_PWD;
	else if (!ft_strcmp(exec->args[0], "unset"))
		exec->builtin = FT_UNSET;
	else if (!ft_strcmp(exec->args[0], "exit"))
		exec->builtin = FT_EXIT;
	else
		exec->builtin = NOT_A_BUILTIN;
}

int	count_pipes(t_token **tokens)
{
	t_token	*current;
	int		count;

	count = 0;
	current = *tokens;
	while (current != NULL)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}
