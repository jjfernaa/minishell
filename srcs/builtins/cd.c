/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dponce-g <dponce-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 00:07:19 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/17 20:11:07 by dponce-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_target_dir(char **args, t_shell *shell)
{
	char	*oldpwd;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		oldpwd = get_env_value_list(shell->env, "HOME");
		if (!oldpwd)
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		return (oldpwd);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		oldpwd = get_env_value_list(shell->env, "OLDPWD");
		if (!oldpwd)
		{
			write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
			return (NULL);
		}
		printf("%s\n", oldpwd);
		return (oldpwd);
	}
	return (args[1]);
}

static void	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		add_env_var(&shell->env, "OLDPWD", old_pwd);
		add_env_var(&shell->env, "PWD", new_pwd);
		free(new_pwd);
	}
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*target_dir;
	char	*old_pwd;

	target_dir = get_target_dir(args, shell);
	if (!target_dir)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target_dir) != 0)
	{
		perror("minishell: cd: ");
		free(old_pwd);
		return (1);
	}
	update_pwd_vars(shell, old_pwd);
	free(old_pwd);
	return (0);
}
