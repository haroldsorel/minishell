/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:19:28 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/16 17:19:30 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_env_var(char **env, char *var) //this function gets the corresponding value from the key <var>
{
	int		i;
	char	*res;

	i = 0;
	if (!var || !var[0])
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


char	*get_prompt(t_data *data)
{
	char	*tmp;
	char	*cwd;
	char	*prompt;

	prompt = ft_strjoin(get_env_var(data->env, "USER"), " "); //not necessary
	if (!prompt)
		return (ft_strdup("minishell % "));
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		tmp = ft_strrchr(cwd, '/');
		tmp = ft_strjoin(prompt, ++tmp);
		free(cwd);
		free(prompt);
	}
	else
		tmp = prompt;
	//if (!tmp)
		//ft_crash(data);
	prompt = ft_strjoin(tmp, " % ");
	free(tmp);
	//if (!prompt)
	//	ft_crash(data);
	return (prompt);
}