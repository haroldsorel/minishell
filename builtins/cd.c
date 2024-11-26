/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:48:37 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:48:39 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void		print_error(char *dir, char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[1] != NULL && args[2] != NULL)
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(dir, 2);
}

static int	update_new_pwd(t_data *data)
{
	char	*new_pwd;
	char	*tmp;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
		return (-1);
	tmp = new_pwd;
	new_pwd = ft_strjoin("PWD=", new_pwd);
	free(tmp);
	if (new_pwd == NULL)
		return (-1);
	if (env_add_or_replace(data, "PWD", new_pwd) == -1)
	{
		free(new_pwd);
		return (-1);
	}
	free(new_pwd);
	return (0);
}

static int	update_old_pwd(t_data *data, char *old_pwd)
{
	char	*tmp;

	tmp = old_pwd;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(tmp);
	if (old_pwd == NULL)
		return (-1);
	if (env_add_or_replace(data, "OLDPWD", old_pwd) == -1)
	{
		free(old_pwd);
		return (-1);
	}
	free(old_pwd);
	return (0);
}

static char	*get_dir(t_data *data, char **args)
{
	char	*dir;

	if (args[1] == NULL)
	{
		dir = get_env_variable(data->env, "HOME");
		if (dir == NULL)
			ft_putstr_fd("minishell : cd: HOME not set\n", 2);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		dir = get_env_variable(data->env, "OLDPWD");
		if (dir == NULL)
			ft_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
	}
	else
		dir = args[1];
	return (dir);
}

int	ft_cd(t_data *data, char **args)
{
	char	*old_pwd;
	char	*dir;

	if (args[1] != NULL && args[2] != NULL && args[3] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	dir = get_dir(data, args);
	if (dir == NULL)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (-1);
	if (chdir(dir) == -1)
	{
		free(old_pwd);
		print_error(dir, args);
		return (1);
	}
	if (update_old_pwd(data, old_pwd) == -1)
		return (-1);
	if (update_new_pwd(data) == -1)
		return (-1);
	return (0);
}