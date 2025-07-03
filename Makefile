NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = srcs/main.c \
	srcs/execution/command.c \
	srcs/builtins/pwd.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/parsing/split.c
	

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
