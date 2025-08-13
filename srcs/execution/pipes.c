#include "../../includes/minishell.h"

void	execute_pipeline_real(t_cmd *cmds, t_shell *shell)
{
	int		**pipes;
	pid_t	*pids;
	t_cmd	*current;
	int		cmd_count;
	int		i;

	cmd_count = count_commands(cmds);
	pipes = create_pipes(cmd_count - 1);
	pids = malloc(sizeof(pid_t) * cmd_count);
	current = cmds;
	i = 0;
	while (current && i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_child_pipes(pipes, i, cmd_count);
			execute_single_cmd(current, shell);
		}
		current = current->next;
		i++;
	}
	cleanup_pipeline(pipes, pids, cmd_count, shell);
	free(pids);
}

int	**create_pipes(int	pipe_count)
{
	int	**pipes;
	int	i;

	if (pipe_count <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			handle_pipe_error(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	setup_child_pipes(int **pipes, int cmd_index, int cmd_count)
{
	if (cmd_count < 2)
		return ;
	// Primer comando: solo stdout -> pipe[0][1]
	if (cmd_index == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
	}
	// Ultimo comando: solo stdin <- pipe[cmd_count-2][0]
	else if (cmd_index == cmd_count - 1)
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	// Comandos intermedios: stdin <- pipe[i - 1][0], stdout -> pipe[i][1]
	else
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	// Cerrar todos los pipes en el hijo  (ya duplicados)
	close_all_pipes_in_child(pipes, cmd_count - 1);
}

void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	int		builtin_result;
	char	*path;
	char	**envp;

	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	apply_redirections(cmd);
	builtin_result = execute_builtin(cmd->argv, shell);
	if (builtin_result != -1)
		exit(builtin_result);
	envp = env_to_array(shell->env);
	if (!envp)
		exit(1);
	// Si no es builtin, ejecutar comando externo
	path = find_executable(cmd->argv[0], envp);
	if (!path)
	{
		print_cmd_not_found(cmd->argv[0]);
		free_array(envp);
		exit(127);
	}
	// Generar envp desde t_env para execve
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	free_array(envp);
	exit(126);
}

void	cleanup_pipeline(int **pipes, pid_t *pids, int cmd_count, t_shell *shell)
{
	close_all_pipes(pipes, cmd_count - 1);
	wait_for_children(pids, cmd_count, shell);
	free_pipes(pipes, cmd_count - 1);
}



