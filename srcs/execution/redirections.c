#include "../../includes/minishell.h"

static int	create_heredoc_pipe(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	apply_input_redirections(t_cmd *cmd)
{
	int	fd;

	if (!cmd->infile)
		return ;
	if (cmd->heredoc)
	{
		fd = create_heredoc_pipe(cmd->infile);
		if (fd < 0)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
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
