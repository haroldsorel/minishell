/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:22:25 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/06 17:22:26 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/ioctl.h>
# include <termios.h> 
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"
# define DEFAULT "\001\033[0;39m\002"


char **g_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_bin_node
{
	t_token_type		type;
	int					file_type;
	char				**args;
	struct s_bin_node	*left;
	struct s_bin_node	*right;
}	t_bin_node;

typedef struct s_env
{
	char				**original_env;
	char				***parsed_env;
}	t_env;

t_token		*new_token(t_token_type type, char *value);
void		add_token_to_list(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		handle_quotes(char **input, t_token **tokens);
void		handle_special_chars(char **input, t_token **tokens);
void		handle_word(char **input, t_token **tokens);
t_token		*tokenize_input(char *input);
 void		display_tokens(t_token *tokens);
void		update_quote_status(char c, int *in_quote, char *quote_char);
void		add_word_token_if_valid(char **start, char **input, t_token **tokens);
size_t		ft_strnlen(const char *s, size_t maxlen);
char		*ft_strndup(const char *src, size_t n);


char 		*new_prompt(void);

void		init_env(char **env);
void		free_env(char **env);

t_bin_node  *new_bin_node(t_token_type type);
void	fill_command_arguments(t_bin_node *command_node,
	t_token **tokens, int arg_count);
int	count_command_arguments(t_token *current);
t_bin_node	*create_and_link_redirection(t_token **tokens, t_token *tmp);
t_bin_node	*redirection(t_token **tokens);
t_bin_node	*create_file_node(t_token *token);
t_bin_node  *parser(t_token **tokens);


int			error_checker(const char *input);
int			has_unclosed_quotes(const char *input);
int			has_invalid_redirections(const char *input);
int			has_misplaced_operators(const char *input);
int			has_logical_operators(const char *input);
void		update_quote_counts(char c, int *s_q_count, int *d_q_count);
const char	*skip_spaces(const char *input);
int			is_invalid_operator(const char **input);
void		update_quote_status(char c, int *in_quote, char *quote_char);
void		add_word_token_if_valid(char **start, char **input,
				t_token **tokens);



#endif