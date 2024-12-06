/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:28:04 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/16 17:50:36 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((unsigned char *)(str + i)) = c;
		i++;
	}
	return (str);
}
/*
#include <string.h>
#include <stdio.h>

int main()
{
	int str1[10];
	int str2[10];
	int i = 0;
	ft_memset(str1, 2, 3);
	memset(str2, 2, 3);
	while (i < 10)
	{
		printf("%d\n", str1[i]);
		printf("%d\n", str2[i]);
		i++;
	}
}
*/
