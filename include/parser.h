/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:01:07 by tonio             #+#    #+#             */
/*   Updated: 2025/10/25 18:09:24 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdbool.h>

typedef enum e_token_type
{
	WORD,
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // <<
	APPEND, // >>
	PIPE, // |
}					t_token_type;

typedef enum s_quote_type
{
	NO_QUOTE,
	SQUOTE,
	DQUOTE,
}					t_quote_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote_type;
	bool			should_merge;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_command
{
	char				**args;
	char				*infile;
	char				*outfile;
	int					append;
	char				*heredoc;
	struct s_command	*next;
	struct s_command	*prev;
}					t_command;

int			process_token(t_command *cmd, t_token **token, int *i);
int			process_special_token(t_command *cmd, t_token **token);
int			alloc_args(t_command *cmd, int ac);
int			count_args_cmd(t_token *token);
t_command	*init_command(void);
void		free_command(t_command *cmd);
t_token		*init_token(void);
void		free_tokens(t_token *token);
void		add_token_back(t_token **list, t_token *new_token);
#endif