/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:08:08 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/05 12:31:59 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
	{
		return (src_len);
	}
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
/*
int main()
{
	char dest1[30];
	char dest2[30];
	char source[] = "qwerty";
	int n1 = ft_strlcpy(dest1, source, 3);
	int n2 = strlcpy(dest2, source, 3);
	printf("%d %s\n", n1, dest1);
	printf("%d %s\n", n2, dest2);
}
*/
