/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:35:17 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/06 17:35:19 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell_crash(t_data *data, t_steps step)
{
	free_array_of_pointers(data->env);
	data->status = 1;
	if (step == TOKENIZATION)
	{
		if (data->input != NULL)
			free(data->input);
		free_tokens(&(data->tokens));
	}
	if (step == PARSING)
	{
		free(data->input);
		free_tokens(&(data->tokens));
		if (data->exec != NULL)
			free(data->exec);
	}
	if (step == EXECUTION)
	{
		free(data->input);
		free_tokens(&(data->tokens));
		free_commands(data);
	}
	rl_clear_history();
	exit(data->status);
}

void	exit_minishell(t_data *data)
{
	free_all(data);
	free_array_of_pointers(data->env);
	rl_clear_history();
	g_signal = 0;
	exit(data->status);
}
