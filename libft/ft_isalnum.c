/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:08:23 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/10/05 11:14:39 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) == 1 || ft_isalpha(c) == 1)
	{
		return (1);
	}
	return (0);
}
/*
int main()
{
	char c = '\r';
	printf("%d", ft_isalnum(c));
}
*/
