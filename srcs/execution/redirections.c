#include "../../includes/minishell.h"

static void	apply_input_redirections(t_cmd *cmd)
{
	int	fd;

	if (!cmd->infile)
		return ;
	// Imput redirecciones (< file 0 << heredoc)
	if (cmd->heredoc)
	{
		// TODO: implementar heredoc despues
		return ;
	}
	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror(cmd->infile);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	apply_output_redirection(t_cmd *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->outfile)
		return ;
	flags = O_CREAT | O_WRONLY;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->outfile);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections(t_cmd *cmd)
{
	if (!cmd)
		return ;
	apply_input_redirections(cmd);
	apply_output_redirection(cmd);
}
