/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 01:37:52 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/08 01:06:10 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
		i++;
	}
	return (dst);
}
/*
int main()
{
	char str[] = "je test ma fonction";
	char *str2 = malloc(sizeof(char) * 20);
	char *str3 = malloc(sizeof(char) * 20);
	if (str2 == NULL || str3 == NULL)
		return (1);
	ft_memcpy(NULL, NULL, 20);
	memcpy(NULL, NULL, 20);
	printf("no problems until now\n");
	printf("%s", str2);
	printf("%s", str3);
	free(str2);
	return (0);
}
*/
