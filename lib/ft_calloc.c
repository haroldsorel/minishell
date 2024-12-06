/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:19:08 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/12/12 19:01:34 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if ((size != 0 && (count * size) / size != count)
		|| (count >= INT_MAX && size >= INT_MAX))
		return (NULL);
	ptr = malloc(count * size);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (i < count * size)
	{
		*(unsigned char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>
int main()
{
	size_t	size = INT_MAX;
	size_t	count = 10000;
	
 	void * d1 = ft_calloc(count, size);
 	void * d2 = calloc(count, size);
}
*/
