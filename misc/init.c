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

static int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

//void	free_env(char **envv)
//{
	//int	i;
	//int	j;

	//j = 0;
	//i = env_len(envv);
	//while (j < i)
	//{
	//	free(envv[j]);
	//	envv[j] = NULL;
	//	j++;
	//}
	//free(envv);
	//envv = NULL;
//}

static void	*init_env(t_data *data, char **env)
{
	int	i;

	data->env = malloc(sizeof(char *) * (env_len(env) + 1));
    if (data->env == NULL)
        return (NULL); //or exit?
	i = 0;
	while (env[i] != NULL)
	{
		data->env[i] = ft_strdup(env[i]);
        if (data->env[i] == NULL)
            return (NULL); //free the already allocated list 
		i++;
	}
	data->env[i] = NULL;
	return (data->env);
}


static int init_signals()
{
    return (1);
}

static void    init_data(t_data *data)
{
    data->args = NULL;
    data->tokens = NULL;
    data->exec = NULL;
    data->input = NULL;
    data->env = NULL;
    data->status = 0;
    data->pid = 0;
	data->exec_size = 0;
}

void init_all(t_data *data, char **env)
{
    init_data(data);
    init_signals();
    init_env(data, env); //malloc
}

