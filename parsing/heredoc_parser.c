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

int	input_handler(t_data *data, t_token *token, int *end)
{
	char	*input;

	input = readline(">");
    (void)data; //temp
	if (input == NULL)
		return (-1);
	while (input != NULL && strcmp(input, token->value)) //change strcmp
	{
		//buff = expand(data, input); //implement expand function, see how it relates to the one in tokenize
		write(end[1], input, ft_strlen(input));
		free(input);
		input = readline(">");
	}
	free(input);
	close(end[1]);
    return (0);
}

int fill_input(t_data *data, t_exec *exec, int *end, int old_stdin)
{
    (void)data;
	//if (g_signal == SIGINT)
	//	data->status = 1;
	close(end[1]);
	//signal(SIGINT, sig_interrupt);
	dup2(old_stdin, STDIN_FILENO);
	if (exec->in_file > 2)
		close(exec->in_file);
	if (exec->in_file > -1)
		exec->in_file = end[0];
    return (0);
}

int heredoc_handler(t_data *data, t_token *token, t_exec *exec)
{
    int pid;
    int end[2];
    int old_stdin;

    old_stdin = dup(STDIN_FILENO); //stores to restore it later
    //signal(SIGINT, sig_interrupt_exec);
    pipe(end);
    pid = fork();
    if (pid < 0)
        return (-1);
    if (pid == 0)
    {
        //signal(SIGINT, SIG_DFL);
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

int heredoc_parser(t_data *data, t_token *current, t_exec *exec)
{
	while (current != NULL && current->type != PIPE)
    {
        if (current->type == HEREDOC)
        {
            if (heredoc_handler(data, current, exec) == -1)
				return (-1);
        }
        current = current->next;
	}
	return (0);
}