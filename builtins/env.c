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

void	print_line(char *line)
{
	char	*key;
	char	*value;

	value = ft_strchr(line, '=');
	key = ft_substr(line, 0, value - line);
	if (key == NULL)
		return ;
	if (value == NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(line, 1);
	}
	else
	{
		value++;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(key, 1);
		write(1, "=\"", 2);
		ft_putstr_fd(value, 1);
		write(1, "\"\n", 2);
	}
	free(key);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

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
