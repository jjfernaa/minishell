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
	$(EXECUTION_DIR)/execute.c \
	$(EXECUTION_DIR)/external_commands.c \
	$(EXECUTION_DIR)/path_utils.c \
	$(EXECUTION_DIR)/path_helpers.c \
	$(EXECUTION_DIR)/pipeline.c \
	$(EXECUTION_DIR)/pipes.c \
	$(EXECUTION_DIR)/pipes_utils.c \
	$(EXECUTION_DIR)/pipes_helpers.c \
	$(EXECUTION_DIR)/redirections.c \
	$(EXECUTION_DIR)/redirections_utils.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/exit.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/unset.c \
	$(SIGNALS_DIR)/signals.c \
	$(UTILS_DIR)/cleanup_utils.c \
	$(UTILS_DIR)/utils.c \
	$(EXPANDER_DIR)/expander.c \
	$(EXPANDER_DIR)/expander_segments.c \
	$(LEXER_DIR)/lexer_segments.c \
	$(LEXER_DIR)/lexer_concatenation.c
	
OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/,$(SRC_MAIN:.c=.o)) $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@) #Crea las subcarpetas necesarias
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
