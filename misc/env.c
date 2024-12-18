/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:01:37 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/18 17:01:38 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (0);
	while (env[i] != NULL)
		i++;
	return (i);
}

char	*get_env_variable(char **env, char *var)
{
	int		i;
	char	*res;

	i = 0;
	if (!var || !var[0] || env == NULL)
		return (NULL);
	while ((env[i] && ft_strncmp(env[i], var, ft_strlen(var)))
		|| (env[i] && env[i][ft_strlen(var)] != '='))
		i++;
	if (env[i])
	{
		res = ft_strchr(env[i], '=');
		res++;
		return (res);
	}
	return (NULL);
}
