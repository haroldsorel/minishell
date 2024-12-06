/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:09:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/12/12 19:11:54 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	skip(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long int	res;
	long int	temp;
	int			sign;

	res = 0;
	temp = 0;
	sign = 1;
	str += skip((char *)str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (temp > res && sign > 0)
			return (-1);
		else if (temp > res && sign < 0)
			return (0);
		str++;
		temp = res;
	}
	return (res * sign);
}
