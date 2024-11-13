/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:10:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/08 16:10:09 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*tokens;
	char	*cwd;

	if (argc > 0 && argv)
	{
		//cmd_signals(0);
		init_env(env);
		tokens = NULL;
		cwd = new_prompt();
		input = readline(cwd);
		while (input != NULL)
		{
            tokens = tokenize_input(input);
            display_tokens(tokens);
			//main_exec(&input, &tokens);
			//ft_free(input);
			//ft_free(cwd);
			cwd = new_prompt();
			//cmd_signals(0);
			input = readline(cwd);
		}
		free_env(g_env);
	}
}
