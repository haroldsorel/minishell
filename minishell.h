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
# include <termios.h>
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

typedef enum e_steps
{
	USER_INPUT,
	TOKENIZATION,
	PARSING,
	EXECUTION,
}	t_steps;

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
	S_HEREDOC,
	INFILE,
	OUTFILE,
	APPEND,
	FT_SPACE,
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
	char	*input;
	int		status;
	int		pid;
	int		exec_size;
	t_token	*tokens;
	t_exec	*exec;
}	t_data;

int		g_signal;

int		init_all(t_data *data, char **env);

char	*prompt_launcher(t_data *data);

void	free_tokens(t_token **tokens);
int		handle_word(t_token **tokens, char *input, int *i);
int		handle_quotes(t_token **tokens, char *input, int *i);
int		handle_dquotes(t_token **tokens, char *input, int *i);
int		handle_pipe(t_token **tokens, int *i);
int		add_token_to_list(t_token **tokens, t_token_type type, char *value);
char	*extract_word_from_quote(char *line, int *i, char quote);
int		handle_append(t_token **tokens, char *input, int *i);
int		handle_heredoc(t_token **tokens, char *input, int *i);
int		handle_infile(t_token **tokens, char *input, int *i);
int		handle_outfile(t_token **tokens, char *input, int *i);
int		tokenizer(t_data *data, char *input);

char	*get_env_variable(char **env, char *var);
int		env_len(char **env);
int		env_add(t_data *data, char *str);
int		env_add_or_replace(t_data *data, char *variable, char *str);
int		is_in_env(char **env, char *var);
void	sort_env(char **env);

int		expander(t_data *data);

void	sig_interrupt(int signal);
void	disable_signal_print(void);
void	enable_signal_print(void);
void	sig_quit(int signal);
void	sig_interrupt_exec(int signal);	
char	*ft_insert(char *old_str, char *new_str, int i, int j);
int		count_pipes(t_token **tokens);
int		concatenater(t_token **tokens);

void	free_one_token(t_token *token);
void	*free_array_of_pointers(char **array);
void	exit_minishell(t_data *data);
void	exit_minishell_crash(t_data *data, t_steps step);

int		syntax_checker(t_data *data, char *input);
int		syntax_error_handler(char *str);
int		quotes_skipper(char *input, int *i);

int		parser(t_data *data);
int		file_parser(t_token *token, t_exec *exec);
int		count_args(t_token *tokens);
int		args_parser(t_data *data, t_token *token, t_exec *exec);
int		heredoc_parser(t_data *data, t_token *token, t_exec *exec);
void	parse_builtin(t_exec *exec);
char	*heredoc_handle_special_variable(t_data *data, char *word, int *i);
char	*heredoc_handle_env_variable(t_data *data, char *word, int *i);
int		path_parser(t_data *data, t_exec *exec, char *cmd);

int		ft_env(t_data *data);
int		ft_pwd(t_data *data);
int		ft_echo(char **args);
int		ft_exit(t_data *data, char **args);
int		ft_cd(t_data *data, char **args);
int		ft_unset(t_data *data, char **args);
int		ft_export(t_data *data, char **args);
int		ft_strcmp_env(char *s1, char *s2);

int		executer(t_data *data);
int		builtin_handler(t_data *data, t_exec *exec, t_builtin type);
int		pipe_executor(t_data *data, int i, int in, int out);
int		ft_strcmp(char *s1, char *s2);
void	rl_replace_line(const char *str, int undo);
void	rl_clear_history(void);
void	*free_commands(t_data *data);
void	free_all(t_data *data);
int		is_directory(const char *path);
void	print_line(char *line);
int		no_value_handler(t_data *data, char *var);
int		is_valid_var(char *v);

char	*get_next_line(int fd);
void	check_for_empty_token(t_token *token, t_token **head);
#endif