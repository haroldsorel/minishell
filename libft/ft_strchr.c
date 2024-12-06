/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:30:13 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/08 01:39:19 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (*str == (char)c)
	{
		return ((char *)str);
	}
	return (NULL);
}
/*
int main()
{
	char s1[] = "teste";
	char s2[] = "teste";
	char c = 'e';
	printf("%s\n", ft_strchr(s1, 't' + 256));
	printf("%s\n", strchr(s2, 't' + 256));
	return (0);
}
*/
