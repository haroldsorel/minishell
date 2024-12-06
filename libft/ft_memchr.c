/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:19:19 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/18 19:58:06 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)(s + i)) == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char str1[] = "abcdefghijklmnopqrstuvwxyz";
	char str2[] = "abcdefghijklmnopqrstuvwxyz";
	printf("%s\n",(char *)ft_memchr(str1, 't', 26));
	printf("%s\n", (char *)memchr(str2, 't', 26));
	return (0);
}
*/
