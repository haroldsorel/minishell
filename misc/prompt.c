/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:19:28 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/16 17:19:30 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char *get_prompt(void)
{
	char	*tmp;
	char	*cwd;
	char	*prompt;

    prompt = ft_strdup("");
    if (prompt == NULL)
        return (NULL); //follow up
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		tmp = ft_strrchr(cwd, '/');
        tmp++;
		tmp = ft_strjoin(prompt, tmp);
		free(cwd);
		free(prompt);
	}
	else
		tmp = prompt;
	prompt = ft_strjoin(tmp, " -> ");
	free(tmp);
	if (!prompt)
		return (NULL); //folow up
	return (prompt);
}

char    *prompt_launcher(t_data *data)
{
    char    *prompt;
    char    *user_input;

    prompt = get_prompt();
    if (prompt == NULL)
        return (NULL);
    user_input = readline(prompt);
    free(prompt);
	if (user_input == NULL)
		return (NULL);
    data->input = ft_strtrim(user_input, " \t\n\v\f\r");
    free(user_input);
    if(data->input == NULL)
        return (NULL);
    return (prompt);
}