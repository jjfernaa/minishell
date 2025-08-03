NAME = minishell
TEST_ENV = test_env
TEST_PARSER = test_parser

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I includes -I libft
LEXER_DIR = srcs/lexer
PARSER_DIR = srcs/parser
ENV_DIR = srcs/env
UTILS_DIR = srcs/utils
SRC_MAIN = srcs/main.c
SRC_TESTER_ENV = tester/main_env.c
SRC_TESTER_PARSER = tester/main_parser.c
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
	$(ENV_DIR)/env_to_array.c \
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
	srcs/signals/signal_handlers.c \
	$(UTILS_DIR)/cleanup_utils.c \
	$(UTILS_DIR)/error_utils.c \
	$(UTILS_DIR)/utils.c

OBJS = $(SRC_MAIN:.c=.o) $(SRCS:.c=.o)
OBJS_TEST_ENV = $(SRC_TESTER_ENV:.c=.o) $(SRCS:.c=.o)
OBJS_TEST_PARSER = $(SRC_TESTER_PARSER:.c=.o) $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(TEST_ENV): $(OBJS_TEST_ENV) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_TEST_ENV) $(LIBFT) -lreadline -o $(TEST_ENV)

$(TEST_PARSER): $(OBJS_TEST_PARSER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_TEST_PARSER) $(LIBFT) -lreadline -o $(TEST_PARSER)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

testenv: $(TEST_ENV)
	./$(TEST_ENV)

testparser: $(TEST_PARSER)
	./$(TEST_PARSER)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_TEST_ENV)
	rm -f $(OBJS_TEST_PARSER)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_ENV)
	rm -f $(TEST_PARSER)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re testenv testparser
