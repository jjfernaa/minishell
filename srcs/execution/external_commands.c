#include "../../includes/minishell.h"

static int	execute_command_child(char *path, char **args, t_shell *shell)
{
	execve(path, args, shell->envp);
	perror("execve");
	exit(126);
	return (0);
}

static int	handle_child_process(char **args, t_shell *shell, char *path)
{
	return (execute_command_child(path, args, shell));
}

static int	handle_parent_process(pid_t pid, char *path)
{
	int	status;

	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_external(char **args, t_shell *shell)
{
	pid_t	pid;
	char	*path;

	if (!args || !args[0])
		return (1);
	path = find_executable(args[0], shell->envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		return (handle_child_process(args, shell, path));
	else if (pid > 0)
		return (handle_parent_process(pid, path));
	else
	{
		perror("fork");
		free(path);
		return (1);
	}
}
