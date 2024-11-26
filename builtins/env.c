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

