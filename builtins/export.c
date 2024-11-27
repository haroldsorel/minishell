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

static int  print_export(char **env)
{
    int     i;
    char    **sorted_env;

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
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(sorted_env[i], 1);
        i++;
    }
    free(sorted_env);
    return (0);
}

static int  is_valid_var(char *v)
{
    int     i;

    i = 0;
    while (v[i] != '\0')
    {
        if (ft_isdigit(v[0]) == 1 || (ft_isalnum(v[i]) == 0 && v[i] != '_'))
        {
            ft_putstr_fd("export: not an identifier: ", 2);
            ft_putendl_fd(v, 2);
            return (0);
        }
        i++;
    }
    return (1);
}

int no_value_handler(t_data *data, char *var)
{
    if (is_valid_var(var) == 0)
        return (1);
    if (is_in_env(data->env, var) != -1)
        return (0);
    if (env_add(data, var) == -1)
        return (-1);
    return (0);
}

int export_handler(t_data *data, char *str)
{
    char    *key;
    char    *value;
    int     valid;

    value = ft_strchr(str, '=');
    if (value == NULL)
        return (no_value_handler(data, str));
    key = ft_substr(str, 0, value - str);
    if (key == NULL)
        return (-1);
    valid = is_valid_var(key);
    if (valid == 1 && env_add_or_replace(data, key, str) == -1)
    {
        free(key);
        return (-1);
    }
    free(key);
    if (valid == 1)
        return (0);
    else
        return (1);
}

int ft_export(t_data *data, char **args)
{
    int i;
    int ret;
    int flag;

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