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

typedef enum e_builtin
{
	NOT_A_BUILTIN,
	FT_CD,
	FT_ECHO,
	FT_ENV,
	FT_EXPORT,
	FT_PWD,
	FT_UNSET,
	FT_EXIT,
}	t_builtin;

typedef enum e_token_type
{
	WORD,
	DQUOTE,
	QUOTE,
	PIPE,
	HEREDOC,
	INFILE,
	OUTFILE,
	APPEND,
	SPACE,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_env
{
	char				*name;
	char				*content;
}	t_env;

typedef struct s_exec
{
	t_builtin	builtin;
	int			in_file;
	int			out_file;
	char		*path;
	char		**args;
}	t_exec;


typedef struct s_data
{
	char	**env;
	char	**args;
	char	*input;
	int		status;
	int		pid;
	int		exec_size;
	t_token	*tokens;
	t_exec	*exec;
}	t_data;

void 	init_all(t_data *data, char **env);
char    *prompt_launcher(t_data *data);


void	lexer(t_data *data, char **line);
void    free_tokens(t_token **tokens);
int		handle_word(t_token **tokens, char *input, int *i);
int		handle_quotes(t_token **tokens, char *input, int *i);
int		handle_dquotes(t_token **tokens, char *input, int *i);
int		handle_pipe(t_token **tokens, int *i);
int		add_token_to_list(t_token **tokens, t_token_type type, char *value);
char    *extract_word_from_quote(char *line, int *i, char quote);
int		handle_append(t_token **tokens, char *input, int *i);
int		handle_heredoc(t_token **tokens, char *input, int *i);
int		handle_infile(t_token **tokens, char *input, int *i);
int		handle_outfile(t_token **tokens, char *input, int *i);
int		tokenizer(t_data *data, char *input);

char	*get_env_variable(char **env, char *var);

int		expander(t_data *data);

int		count_pipes(t_token **tokens);

int		concatenater(t_token **tokens);

void    free_one_token(t_token *token);
void    free_array_of_pointers(char **array);

int		syntax_checker(char *input);
int		syntax_error_handler(char *str);
int		quotes_skipper(char *input, int *i);

int		parser(t_data *data);
void	print_commands(t_data *data, t_exec *exec);
int 	file_parser(t_data *data, t_token *token, t_exec *exec);
int		count_args(t_token *tokens);
int		args_parser(t_token *token, t_exec *exec);
int		heredoc_parser(t_data *data, t_token *token, t_exec *exec);
void	fill_builtin(t_exec *exec, int	execsize);

void	ft_env(t_data *data);
void	ft_pwd(t_data *data);
void    ft_echo(char **args);
int		ft_exit(t_data *data, char **args);


int		executer(t_data *data);

int		ft_strcmp(char *s1, char *s2);

#endif