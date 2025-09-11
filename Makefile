NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

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
	$(EXECUTION_DIR)/redirections.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/exit.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/unset.c \
	$(SIGNALS_DIR)/signals.c \
	$(UTILS_DIR)/string_utils.c \
	$(UTILS_DIR)/cleanup_utils.c \
	$(UTILS_DIR)/error_utils.c \
	$(UTILS_DIR)/utils.c \
	$(EXPANDER_DIR)/expander.c \
	
OBJS = $(SRC_MAIN:.c=.o) $(SRCS:.c=.o)

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
