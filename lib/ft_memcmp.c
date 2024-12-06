/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:36:17 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/05 15:45:57 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *((unsigned char *)(s1 + i))
		== *((unsigned char *)(s2 + i)))
	{
		i++;
	}
	if (i < n)
	{
		return (*(unsigned char *)(s1 + i)
			- *(unsigned char *)(s2 + i));
	}
	return (0);
}
/*
int main()
{
	char str1[] = "abc";
	char str2[]  = "abd";
	printf("%d\n", ft_memcmp(str1, str2, 3));
	printf("%d\n", memcmp(str1, str2, 3));
	return (0);
}
*/
