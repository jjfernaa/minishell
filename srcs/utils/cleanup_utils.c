#include "minishell.h"

void	cleanup_loop(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmd)
		free_cmds(shell->cmd);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	cleanup_loop(shell);
	if (shell->env)
		free_env(shell->env); //Si la estructura t_shell no es un * en main, no puedo utilizar free_env
/* 	if (data->infile_fd >= 0)
		close(data->infile_fd);
	if (data->outfile_fd >= 0)
		close(data->outfile_fd);
	if (data->pipe_fd[0] >= 0)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] >= 0)
		close(data->pipe_fd[1]); */
}

void	cleanup_exit(t_shell *shell, int exit_code)
{
	cleanup_shell(shell);
	exit(exit_code);
}
