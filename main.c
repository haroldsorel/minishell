/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:19:19 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/16 17:19:20 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	minishell_launcher(t_data *data)
{
	int	flag;

	while (1)
	{
		flag = 0;
		if (prompt_launcher(data) == NULL)
			return (exit_minishell_crash(data, USER_INPUT), -1);
		if (data->input[0] == '\0' || syntax_checker(data->input) == -1)
			flag = 1;
		if (flag == 0 && tokenizer(data, data->input) == -1)
			return (exit_minishell_crash(data, TOKENIZATION), -1);
		if (flag == 0 && parser(data) == -1)
			flag = 1;
		if (flag == 0 && g_signal != SIGINT && executer(data) == -1)
			return (exit_minishell_crash(data, EXECUTION), -1);
		add_history(data->input);
		free_all(data);
		//free_array_of_pointers(data->env);
		//return (0);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (init_all(&data, env) == -1)
		return (1);
	if (minishell_launcher(&data) == -1)
		return (1);
	return (0);
}