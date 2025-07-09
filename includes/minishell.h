
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "lexer.h"

// Structures
typedef struct s_shell
{
	char	**envp;
	int		exit_status;
}	t_shell;

// Main functions
void	process_command(char *input, t_shell *shell);

// Builtin functions
int		builtin_pwd(void);
int		builtin_echo(char **args);
int		builtin_env(t_shell *shell);
int		builtin_cd(char **args);
int		builtin_exit(char **args, t_shell *shell);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);

// Parsing functions
char	**split_input(char *input);
void	free_args(char **args);

#endif