/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-jof <juan-jof@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:22:56 by juan-jof          #+#    #+#             */
/*   Updated: 2025/09/24 20:22:59 by juan-jof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_redir
{
	char			*filename;
	int				type;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*input_redirs;
	t_redir			*output_redirs;
	int				heredoc;
	struct s_cmd	*next;
}	t_cmd;

int		validate_tokens(t_token *token);
t_cmd	*parse_tokens(t_token *tokens);

int		is_redir(t_token *token);
t_redir	*new_redir(char *filename, int type);
void	add_redir(t_redir **redir_lis, char *filename, int type);
void	free_cmds(t_cmd *cmd);

#endif
