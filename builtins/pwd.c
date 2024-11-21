/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:49:25 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/21 18:49:26 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		data->status = 1; //use this or return?
		return ;
	}
	write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
	free(pwd);
	data->status = 0; //use this or return
}
