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

static int  is_valid_var(char *v)
{
    int     i;

    i = 0;
    while (v[i] != '\0')
    {
        if (ft_isdigit(v[0]) == 1 || (ft_isalnum(v[i]) == 0 && v[i] != '-'))
        {
            ft_putstr_fd("export: not an identifier: ", 2);
            ft_putendl_fd(v, 2);
            return (0);
        }
        i++;
    }
    return (1);
}

int export_handler(t_data *data, char *str)
{
    char    *key;
    char    *value;
    int     valid;

    value = ft_strchr(str, '=');
    if (value == NULL)
    {
        //understand this more
        return (0);
    }
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
        //print_export(data, args);
        return (0);
    }
    while (args[i] != NULL)
    {
        ret = export_handler(data, args[i]) == -1;
        if (ret == -1)
            return (-1);
        if (ret == 1)
            flag = 1;
        i++;
    }
    return (flag);
}