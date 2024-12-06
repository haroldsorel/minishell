/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:24:44 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/18 20:05:13 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == sep)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && str[i] != sep)
			i++;
	}
	return (count);
}

static char	**malloc_and_free_list(char **list, int index, int *count)
{
	int	i;

	i = 0;
	list[index] = malloc(sizeof(char) * (*count + 1));
	if (list[index] == NULL)
	{
		while (list[i] != NULL)
		{
			free(list[i]);
			i++;
		}
		free(list);
		return (NULL);
	}
	*count = 0;
	return (list);
}

static char	**initialize(char **array, const char *str, char sep)
{
	int	i;
	int	count;
	int	array_index;

	i = 0;
	count = 0;
	array_index = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == sep)
			i++;
		while (str[i] != '\0' && str[i] != sep)
		{
			count++;
			i++;
		}
		if (count > 0)
		{
			if (malloc_and_free_list(array, array_index, &count) == NULL)
				return (NULL);
			array_index++;
		}
	}
	array[array_index] = NULL;
	return (array);
}

static char	**fill_in(char **list, char const *str, char c)
{
	int		i;
	int		list_index;
	int		str_index;

	i = 0;
	list_index = 0;
	str_index = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		while (str[i] != '\0' && str[i] != c)
		{
			list[list_index][str_index] = str[i];
			i++;
			str_index++;
			list[list_index][str_index] = '\0';
		}
		str_index = 0;
		list_index++;
	}
	return (list);
}

char	**ft_split(const char *str, char c)
{
	char	**list;

	if (str == NULL)
		return (NULL);
	list = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (list == NULL)
		return (NULL);
	if (initialize(list, str, c) == NULL)
		return (NULL);
	fill_in(list, str, c);
	return (list);
}
/*
#include <stdio.h>
int main()
{
	const char str[] = "       qw f b srt gasergas adsfa sase a ef f f      ";
	char sep = ' ';
	char **list = ft_split("hello!", ' ');
	int i = 0;
	while (list[i] != NULL)
	{
		printf("%s\n", list[i]);
		i++;
	}
	return (0);
}
*/
