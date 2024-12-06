/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:40:40 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/18 20:02:11 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (*(s + i) != '\0')
	{
		(*f)(i, (s + i));
		i++;
	}
}
/*
void fun(unsigned int x, char *c)
{
	*c = *c + x;
}

int main()
{
	char str[] = "11111111";
	ft_striteri(str, &fun);
	printf("%s", str);
}
*/
