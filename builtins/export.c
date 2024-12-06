/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:49:14 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:49:15 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	print_export(char **env)
{
	int		i;
	char	**sorted_env;

	i = 0;
	sorted_env = malloc(sizeof(char *) * (env_len(env) + 1));
	if (sorted_env == NULL)
		return (-1);
	while (env[i] != NULL)
	{
		sorted_env[i] = env[i];
		i++;
	}
	sorted_env[i] = NULL;
	sort_env(sorted_env);
	i = 0;
	while (sorted_env[i] != NULL)
	{
		print_line(sorted_env[i]);
		i++;
	}
	return (free(sorted_env), 0);
}

int	export_increment(t_data *data, char *str)
{
	char	*new;
	char	*value;
	char	*key;

	value = ft_strchr(str, '=');
	key = ft_substr(str, 0, value - str - 1);
	if (key == NULL)
		return (-1);
	if (is_valid_var(key) == 0)
		return (1);
	if (is_in_env(data->env, key) == -1)
		new = ft_strjoin(key, value);
	else
		new = ft_strjoin((data->env)[is_in_env(data->env, key)], ++value);
	if (new == NULL)
		return (free(key), -1);
	if (env_add_or_replace(data, key, new) == -1)
		return (-1);
	free(key);
	free(new);
	return (0);
}

int	export_add_or_replace(t_data *data, char *str)
{
	char	*value;
	char	*key;
	int		ret;
	int		valid;

	value = ft_strchr(str, '=');
	if (value == NULL)
		return (no_value_handler(data, str));
	key = ft_substr(str, 0, value - str);
	if (key == NULL)
		return (-1);
	valid = is_valid_var(key);
	if (valid == 1 && env_add_or_replace(data, key, str) == -1)
		return (free(key), -1);
	if (valid == 1)
		ret = 0;
	else
		ret = 1;
	free(key);
	return (ret);
}

int	export_handler(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || (str[0] == '+' && str[1] == '='))
	{
		ft_putstr_fd("export: not an valid identifier: ", 2);
		ft_putendl_fd(str, 2);
		return (1);
	}
	while (str[i] != '\0' && str[i] != '+')
		i++;
	if (str[i] == '+')
	{
		if (str[i + 1] == '=')
			return (export_increment(data, str));
		else
		{
			ft_putstr_fd("export: not an valid identifier: ", 2);
			ft_putendl_fd(str, 2);
			return (1);
		}
	}
	else
		return (export_add_or_replace(data, str));
	return (0);
}

int	ft_export(t_data *data, char **args)
{
	int	i;
	int	ret;
	int	flag;

	i = 1;
	flag = 0;
	if (args[1] == NULL)
	{
		if (print_export(data->env) == -1)
			return (-1);
		return (0);
	}
	while (args[i] != NULL)
	{
		ret = export_handler(data, args[i]);
		if (ret == -1)
			return (-1);
		if (ret == 1)
			flag = 1;
		i++;
	}
	return (flag);
}
