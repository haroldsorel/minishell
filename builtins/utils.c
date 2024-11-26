/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:20:15 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/25 13:20:24 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strcmp_env(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void *env_fill(char  **new_env, char **old_env)
{
    int i;

    i = 0;
    while (old_env[i] != NULL)
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (new_env[i] == NULL)
        {
            free_array_of_pointers(new_env);
			return (NULL);
        }
		i++;
	}
    return (new_env);
}

int	env_add(t_data *data, char *str)
{
	char	**new_env;
	int		new_len;

    if (data->env == NULL)
        return (-1);
	new_len = env_len(data->env) + 1;
	new_env = malloc(sizeof(char *) * (new_len + 1));
	if (new_env == NULL)
		return (-1);
	if (env_fill(new_env, data->env) == NULL)
        return (-1);
	new_env[new_len - 1] = ft_strdup(str);
	if (new_env[new_len - 1] == NULL)
    {
        free_array_of_pointers(new_env);
		return (-1);
    }
	new_env[new_len] = NULL;
	free_array_of_pointers(data->env);
	data->env = new_env;
	return (0);
}

int	is_in_env(char **env, char *var)
{
	int	i;
	int	j;
	int	len;

	len = env_len(env);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (env[i][j] != '\0' && env[i][j] != '=' && var[j] != '\0' && env[i][j] == var[j])
			j++;
		if (env[i][j] == '=' && var[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}


int	env_add_or_replace(t_data *data, char *variable, char *str)
{
    int     index;

    index = is_in_env(data->env, variable);
    if (index == -1)
    {
        if (env_add(data, str) == -1)
           return (-1);
        return (0);
    }
    if (data->env[index] != NULL)
        free(data->env[index]);
    data->env[index] = ft_strdup(str);
    if (data->env[index] == NULL)
        return (-1);
    return (0);
}
