NAME = minishell
TEST = tester

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I includes -I libft
LEXER_DIR = srcs/lexer
PARSER_DIR = srcs/parser
SRC_MAIN = srcs/main.c
SRC_TESTER = tester/main_test.c
SRCS =  \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/lexer_utils.c \
	$(PARSER_DIR)/parser.c \
	srcs/execution/command.c \
	srcs/builtins/pwd.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/builtins/cd.c \
	srcs/builtins/exit.c \
	srcs/builtins/export.c \
	srcs/builtins/unset.c \
	srcs/parsing/split.c \
	srcs/signals/signals.c \
	srcs/signals/signal_handlers.c
	
OBJS = $(SRC_MAIN:.c=.o) $(SRCS:.c=.o)
OBJS_TESTER = $(SRC_TESTER:.c=.o) $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(TEST): $(OBJS_TESTER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_TESTER) $(LIBFT) -lreadline -o $(TEST)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_TESTER)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re test
