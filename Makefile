NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I includes -I libft
LEXER_DIR = srcs/lexer
SRCS = srcs/main.c \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/lexer_utils.c \
	srcs/execution/command.c \
	srcs/builtins/pwd.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/builtins/cd.c \
	srcs/builtins/exit.c \
	srcs/builtins/export.c \
	srcs/builtins/unset.c \
	srcs/parsing/split.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
