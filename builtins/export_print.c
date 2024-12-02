/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:13:22 by hsorel            #+#    #+#             */
/*   Updated: 2024/12/02 23:13:24 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_value_handler(t_data *data, char *var)
{
	if (is_valid_var(var) == 0)
		return (1);
	if (is_in_env(data->env, var) != -1)
		return (0);
	if (env_add(data, var) == -1)
		return (-1);
	return (0);
}

int	is_valid_var(char *v)
{
	int	i;

	i = 0;
	if (v[0] == '\0')
	{
		ft_putstr_fd("export: not an valid identifier: ", 2);
		ft_putendl_fd("=", 2);
		return (0);
	}
	while (v[i] != '\0')
	{
		if (ft_isdigit(v[0]) == 1 || (ft_isalnum(v[i]) == 0 && v[i] != '_'))
		{
			ft_putstr_fd("export: not an valid identifier: ", 2);
			ft_putendl_fd(v, 2);
			return (0);
		}
		i++;
	}
	return (1);
}
