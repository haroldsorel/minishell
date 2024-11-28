/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:33:30 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/16 17:33:31 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	increment_shlvl(t_data *data, char **env)
{
	char	*old_value;
	int		new_value_int;
	char	*new_value_char;

	old_value = get_env_variable(env, "SHLVL");
	if (old_value == NULL)
	{
		if (env_add(data, "SHLVL=1") == -1)
			return (-1);
		return (0);
	}
	new_value_int = ft_atoi(old_value);
	new_value_int++;
	new_value_char = ft_itoa(new_value_int);
	if (new_value_char == NULL)
		return (-1);
	old_value = new_value_char;
	new_value_char = ft_strjoin("SHLVL=", new_value_char);
	free(old_value);
	if (new_value_char == NULL)
		return (-1);
	if (env_add_or_replace(data, "SHLVL", new_value_char) == -1)
		return (free(new_value_char), -1);
	free(new_value_char);
	return (0);
}

static void	*init_env(t_data *data, char **env)
{
	int	i;

	data->env = malloc(sizeof(char *) * (env_len(env) + 1));
	if (data->env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		data->env[i] = ft_strdup(env[i]);
		if (data->env[i] == NULL)
		{
			free_array_of_pointers(data->env);
			return (NULL);
		}
		i++;
	}
	data->env[i] = NULL;
	if (increment_shlvl(data, data->env) == -1)
		return (NULL);
	return (data->env);
}

static int	init_signals(void)
{
	g_signal = 0;
	disable_signal_print();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_interrupt);
	return (1);
}

static void	init_data(t_data *data)
{
	data->tokens = NULL;
	data->exec = NULL;
	data->input = NULL;
	data->env = NULL;
	data->status = 0;
	data->pid = 0;
	data->exec_size = 0;
}

int	init_all(t_data *data, char **env)
{
	init_data(data);
	init_signals();
	if (init_env(data, env) == NULL)
		return (-1);
	return (0);
}
