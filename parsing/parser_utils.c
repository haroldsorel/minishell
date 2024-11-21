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

void	print_one_exec(t_exec exec)
{
    printf("COMMAND\n");
	printf("builtin	: %d\n", exec.builtin);
	printf("infile	: %d\n", exec.in_file);
	printf("outfile	: %d\n", exec.out_file);
	printf("path	: %s\n", exec.path);
	printf("Exec Args : ");
	while (*(exec.args) != NULL)
	{
		printf("%s, ", *(exec.args));
		(exec.args)++;
	}
    printf("\n");
}

void	print_commands(t_data *data, t_exec *exec)
{
	int	i;

	i = 0;
	while (i < data->exec_size)
	{
		print_one_exec(exec[i]);
		printf("\n");
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void fill_builtin(t_exec *exec, int	execsize)
{
	int	i;

	i = 0;
	if (!exec || !exec->args || !exec->args[0])
		return ;
	while (i < execsize)
	{
	if (!ft_strcmp(exec[i].args[0], "echo"))
		exec[i].builtin = FT_ECHO;
	else if (!ft_strcmp(exec[i].args[0], "cd"))
		exec[i].builtin = FT_CD;
	else if (!ft_strcmp(exec[i].args[0], "env"))
		exec[i].builtin = FT_ENV;
	else if (!ft_strcmp(exec[i].args[0], "export"))
		exec[i].builtin = FT_EXPORT;
	else if (!ft_strcmp(exec[i].args[0], "pwd"))
		exec[i].builtin = FT_PWD;
	else if (!ft_strcmp(exec[i].args[0], "unset"))
		exec[i].builtin = FT_UNSET;
	else if (!ft_strcmp(exec[i].args[0], "exit"))
		exec[i].builtin = FT_EXIT;
	else
		exec[i].builtin = NOT_A_BUILTIN;
	i++;
	}
}

int count_pipes(t_token **tokens)
{
    t_token *current;
    int     count;

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