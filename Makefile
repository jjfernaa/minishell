NAME = minishell
TEST_ENV = test_env

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I includes -I libft
LEXER_DIR = srcs/lexer
PARSER_DIR = srcs/parser
ENV_DIR = srcs/env
SRC_MAIN = srcs/main.c
SRC_TESTER_ENV = tester/main_env.c
SRCS = \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/lexer_utils.c \
	$(LEXER_DIR)/lexer_conversion.c \
	$(PARSER_DIR)/parser.c \
	$(PARSER_DIR)/parser_utils.c \
	$(PARSER_DIR)/syntax_check.c \
	$(ENV_DIR)/env.c \
	$(ENV_DIR)/env_operations.c \
	$(ENV_DIR)/env_utils.c \
	srcs/execution/command.c \
	srcs/execution/execute.c \
	srcs/execution/external_commands.c \
	srcs/execution/path_utils.c \
	srcs/execution/path_helpers.c \
	srcs/execution/pipeline.c \
	srcs/utils/string_utils.c \
	srcs/builtins/pwd.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/builtins/cd.c \
	srcs/builtins/exit.c \
	srcs/builtins/export.c \
	srcs/builtins/unset.c \
	srcs/signals/signals.c \
	srcs/signals/signal_handlers.c
	
OBJS = $(SRC_MAIN:.c=.o) $(SRCS:.c=.o)
OBJS_TEST_ENV = $(SRC_TESTER_ENV:.c=.o) $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(TEST_ENV): $(OBJS_TEST_ENV) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_TEST_ENV) $(LIBFT) -lreadline -o $(TEST_ENV)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

testenv: $(TEST_ENV)
	./$(TEST_ENV)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_TEST_ENV)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_ENV)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re testenv
