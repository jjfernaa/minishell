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
EXECUTION_DIR = srcs/execution
BUILTINS_DIR = srcs/builtins
SIGNALS_DIR = srcs/signals
UTILS_DIR = srcs/utils
EXPANDER_DIR = srcs/expander
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
	$(EXECUTION_DIR)/command.c \
	$(EXECUTION_DIR)/execute.c \
	$(EXECUTION_DIR)/external_commands.c \
	$(EXECUTION_DIR)/path_utils.c \
	$(EXECUTION_DIR)/path_helpers.c \
	$(EXECUTION_DIR)/pipeline.c \
	$(EXECUTION_DIR)/pipes.c \
	$(EXECUTION_DIR)/pipes_utils.c \
	$(EXECUTION_DIR)/pipes_helpers.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/exit.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/unset.c \
	$(SIGNALS_DIR)/signals.c \
	$(SIGNALS_DIR)/signal_handlers.c \
	$(UTILS_DIR)/string_utils.c \
	$(UTILS_DIR)/cleanup_utils.c \
	$(UTILS_DIR)/error_utils.c \
	$(UTILS_DIR)/utils.c \
	$(EXPANDER_DIR)/expander.c \
	$(UTILS_DIR)/testeo.c

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
