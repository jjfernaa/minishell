/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:23:40 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:23:41 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	**create_keys_array(t_env *env_list)
{
	char	**keys;
	t_env	*current;
	int		size;
	int		i;

	size = 0;
	current = env_list;
	while (current && ++size)
		current = current->next;
	keys = malloc(sizeof(char *) * (size + 1));
	if (!keys)
		return (NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		keys[i++] = current->key;
		current = current->next;
	}
	keys[i] = NULL;
	return (keys);
}

static void	print_exported_vars_from_env(t_env *env_list)
{
	char	**keys;
	t_env	*found;
	int		i;

	keys = create_keys_array(env_list);
	if (!keys)
		return ;
	sort_string_array(keys);
	i = 0;
	while (keys[i])
	{
		found = find_env_var(env_list, keys[i]);
		if (found)
			printf("declare -x %s=\"%s\"\n", found->key, found->value);
		i++;
	}
	free(keys);
}

static int	process_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	if (!is_valid_identifier(arg))
	{
		printf("minishell: export: '%s': not a valid identifier\n", arg);
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
	else if (!find_env_var(shell->env, arg))
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
