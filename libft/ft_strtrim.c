/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:34:56 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/12/12 19:15:36 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_inset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if ((char)set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	find_len(const char *s1, const char *set)
{
	int	i;
	int	count;
	int	slen;

	i = 0;
	count = 0;
	slen = ft_strlen(s1);
	while (s1[i] != '\0' && is_inset(s1[i], set) == 1)
	{
		count++;
		i++;
	}
	if (s1[i] != '\0')
	{
		i = slen - 1;
		while (is_inset(s1[i], set) == 1)
		{
			count++;
			i--;
		}
	}
	return (slen - count);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		strlen;
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || set == NULL)
		return (NULL);
	strlen = find_len(s1, set);
	str = malloc(sizeof(char) * (strlen + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0' && is_inset(s1[i], set) == 1)
		i++;
	while (strlen > 0)
	{
		str[j] = s1[i];
		i++;
		j++;
		strlen--;
	}
	str[j] = '\0';
	return (str);
}
/*
#include <stdio.h>
int main()
{
	const char str[] = "  .... . . . .   ....  .qw. . ... erty      ... . . .    ";
	const char *set = NULL;
	printf("%s", ft_strtrim(str, set));
	return (0);
}
*/
