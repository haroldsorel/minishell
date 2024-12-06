/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:29:29 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/05 14:59:56 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)(ptr + i)) = 0;
		i++;
	}
}
/*
int main()
{
    char str1[] = "bonjour je test ma fonction";
    char str2[] = "Bonjour je test la fonction de base";
    ft_bzero(str1, 5);
    bzero(str2, 5);
    printf("%s", str1);
    printf("%s", str2);
}
*/
