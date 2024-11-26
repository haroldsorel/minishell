/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:49:32 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:49:33 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int  is_valid_var(char *v)
{
    int i;

    i = 0;
    while (v[i] != '\0')
    {
        if (ft_isdigit(v[0]) == 1 || (ft_isalnum(v[i]) == 0 && v[i] != '-'))
        {
            ft_putstr_fd("unset: ", 2);
            ft_putstr_fd(v, 2);
            ft_putstr_fd(": invalid parameter name\n", 2);
            return (0);
        }
        i++;
    }
    return (1);
}

static int  fill_env_exept_index(char **new_env, char **old_env, int index)
{
    int     new_env_i;
    int     old_env_i;

    new_env_i = 0;
    old_env_i = 0;
    while (old_env[old_env_i] != NULL)
    {
        if (old_env_i != index)
        {
            new_env[new_env_i] = ft_strdup(old_env[old_env_i]);
            if (new_env[new_env_i] == NULL)
            {
                free_array_of_pointers(new_env);
                return (-1);
            }
            new_env_i++;
        }
        old_env_i++;
    }
    new_env[new_env_i] = NULL;
    return (0);
}

static int remove_from_env(t_data *data, int index)
{
    char    **new_env;

    new_env = malloc(sizeof(char *) * (env_len(data->env)));
    if (new_env == NULL)
        return (-1);
    if (fill_env_exept_index(new_env, data->env, index) == -1)
        return (-1);
    free_array_of_pointers(data->env);
    data->env = new_env;
    return (0);
}

int     ft_unset(t_data *data, char **args)
{
    int i;
    int ret;
    int valid;
    int index;

    i = 1;
    ret = 0;
    while (args[i] != NULL)
    {
        valid = is_valid_var(args[i]);
        if (valid == 0)
            ret = 1;
        index = is_in_env(data->env, args[i]);
        if (valid == 1 && index != -1)
            if(remove_from_env(data, index) == -1)
                return (-1);
        i++;
    }
    return (ret);
}