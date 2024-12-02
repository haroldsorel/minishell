/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:49:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:49:08 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	skip(char *str, int *i, int *neg)
{
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
	{
		(*i)++;
		*neg = -1;
	}
}

int	str_to_uint8(char *str)
{
	int64_t	int64_res;
	int		neg;
	int		i;
	int		len;

	int64_res = 0;
	neg = 1;
	i = 0;
	len = 0;
	skip(str, &i, &neg);
	while (str[i] != '\0' && ft_isdigit(str[i]) == 1 && len < 19)
	{
		if (int64_res > (INT64_MAX - (str[i] - '0')) / 10)
			break ;
		int64_res = int64_res * 10 + (str[i] - '0');
		i++;
		len++;
	}
	return ((int)((int64_res * neg) % 256));
}

int	valid_argument(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_isdigit(str[i]) == 0 && str[i] != ' ')
		return (0);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ')
			return (0);
		if (str[i] == ' ')
			flag = 1;
		if (flag == 1 && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data, char **args)
{
	int	exit_code;

	exit_code = data->status;
	if (args[1] == NULL)
		exit_minishell(data);
	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (valid_argument(args[1]) == 0)
	{
		data->status = 255;
		ft_putstr_fd("exit: numeric argument required: ", 2);
		ft_putendl_fd(args[1], 2);
		exit_minishell(data);
		return (1);
	}
	exit_code = str_to_uint8(args[1]);
	if (exit_code < 0)
		exit_code = exit_code + 256;
	data->status = exit_code;
	exit_minishell(data);
	return (0);
}
