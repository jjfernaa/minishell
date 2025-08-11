#include "../../includes/minishell.h"

static int	execute_command_child(char *path, char **args, char **envp)
{
	execve(path, args, envp);
	perror("execve");
	exit(126);
	return (0);
}

static int	handle_child_process(char **args, char **envp, char *path)
{
	return (execute_command_child(path, args, envp));
}

static int	handle_parent_process(pid_t pid, char *path, char **envp)
{
	int	status;

	free(path);
	free_array(envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_external(char **args, t_shell *shell)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	if (!args || !args[0])
		return (1);
	envp = env_to_array(shell->env);
	if (!envp)
		return (1);
	path = find_executable(args[0], envp);
	if (!path)
	{
		print_cmd_not_found(args[0]);
		free_array(envp);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		return (handle_child_process(args, envp, path));
	if (pid > 0)
		return (handle_parent_process(pid, path, envp));
	perror("fork");
	free(path);
	free_array(envp);
	return (1);
}


