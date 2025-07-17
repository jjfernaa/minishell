#include "../../includes/minishell.h"

static int	handle_child_process(char **args, t_shell *shell)
{
	execve(args[0], args, shell->envp);
	perror("execve");
	exit(126);
	return (0);
}

static int	handle_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_external(char **args, t_shell *shell)
{
	pid_t	pid;

	if (!args || !args[0])
		return (1);
	if (access(args[0], F_OK | X_OK) != 0)
	{
		printf("minishell: %s: command not found\n", args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		return (handle_child_process(args, shell));
	else if (pid > 0)
		return (handle_parent_process(pid));
	else
	{
		perror("fork");
		return (1);
	}
}
