/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 03:15:48 by juan-jof          #+#    #+#             */
/*   Updated: 2025/08/01 02:31:56 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_exported_vars_from_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf("declare -x %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

static int	process_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		key = ft_substr(arg, 0, equal_pos - arg);
		value = ft_strdup(equal_pos + 1);
		add_env_var(&shell->env, key, value);
		free(key);
		free(value);
	}
	else
		add_env_var(&shell->env, arg, "");
	return (0);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;
	int	error_status;

	if (!args[1])
	{
		print_exported_vars_from_env(shell->env);
		return (0);
	}
	i = 1;
	error_status = 0;
	while (args[i])
	{
		if (process_export_arg(args[i], shell) != 0)
			error_status = 1;
		i++;
	}
	return (error_status);
}

