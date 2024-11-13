NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I. -Ilibft
INCLUDES = minishell.h

SRCS = src/tokenizer/tokenizer.c \
	src/tokenizer/tokenizer_utils.c \
	src/tokenizer/tokenizer_utils_2.c \
	src/tokenizer/input_checker.c \
	src/tokenizer/input_checker_utils.c \
	src/prompt.c \
	src/main.c \
	src/env.c \
	src/parsing/parser.c \
	src/parsing/parser_utils.c
	
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -o $(NAME)

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