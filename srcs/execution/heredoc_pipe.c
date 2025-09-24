#include "../../includes/minishell.h"

/* función pequeña para abrir pipe */
static int	open_pipe(int p[2])
{
	if (pipe(p) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static void	setup_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

/* función que hace fork y que en el hijo lee heredoc */
static pid_t	fork_heredoc_reader(int p[2], char *delimiter)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		close(p[0]);
		setup_heredoc_signals();
		handle_heredoc_input(p, delimiter);
		close(p[1]);
		exit(0);
	}
	return (pid);
}

/* función que espera al hijo y detecta si abortó por SIGINT */
static int	wait_heredoc(pid_t pid, int *read_fd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(*read_fd);
		return (-1);
	}
	return (0);
} 

/* función principal de creación de pipe + fork + espera */
int	create_heredoc_pipe(char *delimiter)
{
	int		p[2];
	pid_t	pid;

	if (open_pipe(p) < 0)
		return (-1);
	signal(SIGQUIT, SIG_IGN);
	pid = fork_heredoc_reader(p, delimiter);
	if (pid < 0)
	{
		close(p[0]);
		close(p[1]);
		setup_signals();
		return (-1);
	}
	close(p[1]);
	if (wait_heredoc(pid, &p[0]) < 0)
	{
		setup_signals();
		return (-1);
	}
	setup_signals();
	return (p[0]);
} 
