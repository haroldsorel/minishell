/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:52:04 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/07 02:09:54 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
	{
		return (src_len + dstsize);
	}
	while (dst[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && j < (dstsize - dst_len - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
/*
int main()
{
	char dest1[10] = "a";
	char dest2[10] = "a";
	char  source[] = "lorem ipsum dolor sit amet";
	int n1 = strlcat(dest1, source, 6);
	int n2 = ft_strlcat(dest2, source, 6);
	printf("%d : %s\n", n1, dest1);
	printf("%d : %s\n", n2, dest2);
	return (0);
}
*/
