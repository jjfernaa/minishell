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
# include "libft.h"
# include "lexer.h"
# include "env.h"
# include "parser.h"
# include "utils.h"

// Structures
typedef struct s_shell
{
	char	*input;
	char	**envp;
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmd;
	int		infile_fd;
	int		outfile_fd;
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

// Signals functions
extern volatile sig_atomic_t	g_signal_received;
void	setup_signals(void);
void	handle_sigint(int sig);

// Execution functions
int		execute_builtin(char **args, t_shell *shell);
int		execute_command(char **args, t_shell *shell);
char	*find_executable(char *command, char **envp);
char	*get_env_value(char *key, char **envp);
char	*check_direct_path(char *command);
char	*search_in_dirs(char **dirs, char *command);
int		execute_external(char **args, t_shell *shell);
int		is_builtin(char *command);

// Utils functions
int		ft_strcmp(const char *s1, const char *s2);

// Pipeline functions
int		has_pipes_or_redirects(t_token *tokens);
void	execute_pipeline(t_cmd *cmds, t_shell *shell);

// Error and clean functions
void	exit_error_cleanup(t_shell *shell, char *message, int code);
void	cleanup_loop(t_shell *shell);
void	cleanup_shell(t_shell *shell);

#endif
