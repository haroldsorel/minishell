/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:52:32 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/08 01:40:04 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
		{
			return ((char *)str + i);
		}
		i--;
	}
	return (NULL);
}
/*
int main()
{
	char str1[] = "abcdefghijklmnopqrstubvwxyz";
	char str2[] = "abcdefghijklmnopqrstubvwxyz";
	char c = '0';
	printf("%s\n", ft_strrchr(str1, c));
	printf("%s\n", ft_strrchr(str2, c));
	return (0);
}
*/
