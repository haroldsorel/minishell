/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:51:31 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/06 18:51:32 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

const char	*get_token_type_name(t_token_type type)
{
 	const char	*token_type_names[7];

 	token_type_names[0] = "WORD";
 	token_type_names[1] = "PIPE";
 	token_type_names[2] = "REDIRECT_IN";
 	token_type_names[3] = "REDIRECT_OUT";
 	token_type_names[4] = "REDIRECT_APPEND";
 	token_type_names[5] = "REDIRECT_HEREDOC";
 	token_type_names[6] = "TOKEN_ENV_VAR";
 	if (type >= 0 && type < 7)
 		return (token_type_names[type]);
 	return ("UNKNOWN");
}

 void	display_tokens(t_token *tokens)
{
 	t_token	*token;

 	token = tokens;
 	while (token)
 	{
 		printf("Token: \033[0;36m %-20s \033[0m |\t \
 			Type: \033[0;35m %-18s \033[0m \n",
 			token->value, get_token_type_name(token->type));
 		printf("--------------------------------------------------\n");
 		token = token->next;
 	}
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strnlen(src, n);
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len])
		len++;
	return (len);
}
