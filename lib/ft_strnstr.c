/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 02:04:30 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/05 16:04:44 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_needle(const char *str, const char *needle)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < ft_strlen(needle))
	{
		return (0);
	}
	while (needle[i] != '\0')
	{
		if (str[i] != needle[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
	{
		return ((char *)haystack);
	}
	while (haystack[i] != '\0' && i + needle_len <= n)
	{
		if (haystack[i] == needle[0]
			&& check_needle(&(haystack[i]), needle) == 1)
		{
			return ((char *)(&(haystack[i])));
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
        char str[] = "abcdefghijklmnopqrstuvwxyz";
        char needle[] = "xyz";
        printf("%s\n", ft_strnstr(str, needle, 26));
	printf("%s\n", strnstr(str, needle, 26));
}
*/
