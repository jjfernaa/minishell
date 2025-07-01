NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = srcs/main.c \
	srcs/execution/command.c \
	srcs/builtins/pwd.c
	

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
