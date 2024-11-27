/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:33:31 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/27 01:33:44 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_directory(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

static void print_error(t_data *data, char *cmd, int flag)
{
    if (flag == 1)
    {
        ft_putstr_fd("command not found: ", 2);
        ft_putendl_fd(cmd, 2);
        data->status = 127;
    }
    if (flag == 2)
    {
        ft_putstr_fd(cmd, 2);
        ft_putendl_fd(": is a directory\n: ", 2);
        data->status = 126;
    }
    if (flag == 3)
    {
        ft_putstr_fd(strerror(errno), 2);
        write(2, ": ", 2);
        ft_putendl_fd(cmd, 2);
        data->status = 127;
    }
}

static char *find_executable(t_data *data, char *cmd, char **hosts, int i)
{
    char    *temp;
    char    *path;

    temp = ft_strjoin(hosts[i], "/");
    if (temp == NULL)
    {
        free_array_of_pointers(hosts);
        exit_minishell_crash(data);
    }
    path = ft_strjoin(temp, cmd);
    free(temp);
    if (path == NULL)
    {
        free_array_of_pointers(hosts);
        exit_minishell_crash(data);
    }
    if (access(path, F_OK | X_OK) != -1)
		return (path);
    free(path);
    return (NULL);
}

static char *find_path(t_data *data, char *cmd)
{
    char    *path;
    char    *path_value;
    char    **hosts;
    int     i;

    path_value = get_env_variable(data->env, "PATH");
    if (path_value == NULL)
    {
        print_error(data, cmd, 1);
        return (NULL);
    }
    hosts = ft_split(path_value, ':');
    i = 0;
    if (hosts == NULL)
        exit_minishell_crash(data);
    while (hosts[i] != NULL)
    {
        path = find_executable(data, cmd, hosts, i);
        if (path != NULL)
            return (free_array_of_pointers(hosts), path);
        i++;
    }
    print_error(data, cmd, 1);
    return (free_array_of_pointers(hosts), path);
}

static int  is_valid_path(t_data *data, char *path)
{
    if (access(path, F_OK | X_OK) != -1)
    {
        if (is_directory(path) == 1)
        {
            print_error(data, path, 2);
            return (0);
        }
        path = ft_strdup(path);
        if (path == NULL)
            exit_minishell_crash(data);
        return (1);
    }
    print_error(data, path, 3);
    if (access(path, F_OK) == -1)
        print_error(data, path, 1);
    return (0);
}

int path_parser(t_data *data, t_exec *exec, char *cmd)
{
    if (cmd == NULL)
        return (0);
    if (exec->builtin != 0)
        return (0);
    if (cmd[0] == '/')
    {
        if (is_valid_path(data, cmd) == 1)
            exec->path = ft_strdup(cmd);
    }
    else if (cmd[0] == '.' && cmd[1] == '/')
    {
        if (is_valid_path(data, cmd) == 1)
            exec->path = ft_strdup(cmd);
    }
    else
        exec->path = find_path(data, cmd);
    return (0);
}