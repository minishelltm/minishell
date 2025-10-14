/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:04:21 by mmicael           #+#    #+#             */
/*   Updated: 2025/10/14 18:54:22 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_token_type
{
	WORD,
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // <<
	APPEND, // >>
}					t_token_type;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

#endif