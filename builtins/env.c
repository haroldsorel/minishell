/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:48:55 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:48:59 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void sort_env(char **env)
{
    int     i;
    int     j;
    int     len;
    char    *temp;

    i = 0;
    len = env_len(env);
    while (i < len - 1) 
    {
        j = 0;
        while (j < len - i - 1)
        {
            if (ft_strcmp_env(env[j], env[j + 1]) > 0)
            {
                temp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strchr(data->env[i], '=') != NULL)
        {
			write(1, data->env[i], ft_strlen(data->env[i]));
            write(1, "\n", 1);
        }
		i++;
	}
	return (0);
}

