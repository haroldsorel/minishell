/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:08:30 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 00:08:46 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*heredoc_expand(t_data *data, char *input, t_token *token)
{
	int	i;

	i = 0;
	if (token->type == S_HEREDOC)
		return (input);
	while (input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] == '?')
			input = heredoc_handle_special_variable(data, input, &i);
		else if (input[i] == '$'
			&& (!ft_isalnum(input[i + 1]) || input[i + 1] == '\0'))
			i++;
		else if (input[i] == '$')
			input = heredoc_handle_env_variable(data, input, &i);
		else
			i++;
		if (input == NULL)
			return (NULL);
	}
	return (input);
}

int	input_handler(t_data *data, t_token *token, int *end)
{
	char	*input;

	input = readline("heredoc>");
	if (input == NULL)
		exit_minishell_crash(data, PARSING);
	while (input != NULL && ft_strcmp(input, token->value))
	{
		input = heredoc_expand(data, input, token);
		write(end[1], input, ft_strlen(input));
		write(end[1], "\n", 1);
		free(input);
		input = readline("heredoc>");
	}
	free(input);
	close(end[1]);
	return (0);
}

int	fill_input(t_data *data, t_exec *exec, int *end, int old_stdin)
{
	if (g_signal == SIGINT)
		data->status = 1;
	close(end[1]);
	signal(SIGINT, sig_interrupt);
	dup2(old_stdin, STDIN_FILENO);
	if (exec->in_file > 2)
		close(exec->in_file);
	if (exec->in_file > -1)
		exec->in_file = end[0];
	return (0);
}

int	heredoc_handler(t_data *data, t_token *token, t_exec *exec)
{
	int	pid;
	int	end[2];
	int	old_stdin;

	old_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sig_interrupt_exec);
	if (pipe(end) == -1)
        exit_minishell_crash(data, PARSING);
	pid = fork();
	if (pid < 0)
		exit_minishell_crash(data, PARSING);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (input_handler(data, token, end) == -1)
			return (-1);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		fill_input(data, exec, end, old_stdin);
	}
	return (0);
}

int	heredoc_parser(t_data *data, t_token *current, t_exec *exec)
{
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == HEREDOC || current->type == S_HEREDOC)
		{
			if (heredoc_handler(data, current, exec) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
