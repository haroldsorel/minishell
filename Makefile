NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I. -Ilibft
READLINE = -lreadline -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib
INCLUDES = minishell.h

SRCS =	main.c \
		misc/init.c \
		misc/prompt.c \
		misc/signal.c \
		misc/free.c \
		misc/env.c\
		misc/expander.c \
		misc/syntax_checker.c \
		misc/syntax_checker_utils.c \
		tokenizer/tokenizer_utils.c \
		tokenizer/handle_quotes.c \
		tokenizer/handle_special_chars.c \
		tokenizer/concatenater.c \
		tokenizer/tokenizer.c \
		parsing/parser.c \
		parsing/parser_utils.c \
		parsing/file_parser.c \
		parsing/args_parser.c \
		parsing/heredoc_parser.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		builtins/utils.c \
		exec/exec_utils.c \
		exec/exec.c \
		exec/pipe_executor.c \
		exec/pipe_executor_utils.c

	
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME):	$(OBJS)
			$(MAKE) bonus -C ./libft
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE) $(LIBFT)

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re