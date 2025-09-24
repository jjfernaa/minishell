/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:23:06 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:23:09 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int		is_symbol(char c);
void	free_array(char **array);
int		ft_strcmp(const char *s1, const char *s2);
void	print_cmd_not_found(const char *cmd);
void	sort_string_array(char **array);

#endif