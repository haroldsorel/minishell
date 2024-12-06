/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 03:01:50 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/07 03:57:11 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n && s1[i] == s2[i])
	{
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
int main() {
    const char *str1 = "1234";
    const char *str2 = "1235";
	size_t n = 3;

    printf("my function : %d\n", ft_strncmp(str1, str2, n));
    printf("C function  : %d\n", strncmp(str1, str2, n));
}
*/
