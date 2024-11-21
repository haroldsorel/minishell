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
	static int	i = 0;
    //int j;

    //j = 0;
    i++;
    printf("COMMAND %d\n", i);
	printf("infile	: %d\n", exec.in_file);
	printf("outfile	: %d\n", exec.out_file);
	printf("path	: %s\n", exec.path);
	printf("Exec Args : ");
	//while (*(exec.args) != NULL)
	//{
	//	j++;
	//	printf("%d : %s, ", i, *(exec.args));
	//	(exec.args)++;
	//}
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