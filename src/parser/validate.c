/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:20:51 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 11:23:37 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"

t_token	*validate(t_token *tks)
{
	t_token	*t;

	t = tks;
	while (t)
	{
		if (t->type == PIPE)
		{
			if (!t->next || !t->prev || t->next->type == PIPE)
			{
				g_exit_code = 258;
				return (write(2, "syntax error\n", 13), free_tokens(tks), NULL);
			}
		}
		else if (t->type == REDIR_IN || t->type == REDIR_OUT
			|| t->type == APPEND || t->type == HEREDOC)
		{
			if (!t->next || t->next->type != WORD)
			{
				g_exit_code = 258;
				return (write(2, "syntax error\n", 13), free_tokens(tks), NULL);
			}
		}
		t = t->next;
	}
	return (tks);
}
