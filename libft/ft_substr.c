/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:29:16 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/18 20:08:42 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	msize(char const *str, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	max_len;

	str_len = ft_strlen(str);
	max_len = str_len - start;
	if (start >= str_len)
		return (0);
	if (len > max_len)
		return (max_len);
	return (len);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	str_size;

	if (str == NULL)
		return (NULL);
	str_size = msize(str, start, len);
	sub = malloc(sizeof(char) * (str_size + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	if (str[i] != '\0' && start < ft_strlen(str))
	{
		while (i < len && str[i] != '\0' && str[start + i] != '\0')
		{
			sub[i] = str[start + i];
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}
/*
int main()
{
	printf("%s", ft_substr("01234", 10, 10));
	return (0);
}
*/
