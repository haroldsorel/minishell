/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:15:19 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/12/11 15:35:03 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_numlen(int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		count++;
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static void	ft_fill(char *str, int n)
{
	int		sign;
	int		i;
	long	num;

	sign = 1;
	i = 0;
	num = n;
	if (num < 0)
	{
		sign = -1;
		num = -num;
	}
	if (num == 0)
		str[i++] = '0';
	while (num != 0)
	{
		str[i++] = (num % 10) + '0';
		num = num / 10;
	}
	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
}

static void	ft_revstr(char *str)
{
	int		i;
	int		len;
	char	temp;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = temp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_numlen(n) + 1));
	if (str == NULL)
		return (NULL);
	ft_fill(str, n);
	ft_revstr(str);
	return (str);
}
/*
int main()
{
	int num = -21474;
	printf("%s\n", ft_itoa(num));
	return (0);
}
*/
