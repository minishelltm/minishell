/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:13:57 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 06:34:22 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int	count_args_cmd(t_token *token)
{
	int		count;
	t_token	*tmp;

	tmp = token;
	count = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && (tmp->prev == NULL
				|| (tmp->prev->type != REDIR_IN
					&& tmp->prev->type != REDIR_OUT
					&& tmp->prev->type != APPEND
					&& tmp->prev->type != HEREDOC)))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	process_special_token(t_command *cmd, t_token **token)
{
	if ((*token)->type == REDIR_IN && (*token)->next->type == WORD)
	{
		cmd->infile = ft_strdup((*token)->next->value);
		if (cmd->infile == NULL)
			return (-1);
		(*token) = (*token)->next;
	}
	else if (((*token)->type == REDIR_OUT || (*token)->type == APPEND)
		&& (*token)->next->type == WORD)
	{
		cmd->outfile = ft_strdup((*token)->next->value);
		if (cmd->outfile == NULL)
			return (-1);
		cmd->append = ((*token)->type == APPEND);
		(*token) = (*token)->next;
	}
	else if ((*token)->type == HEREDOC && (*token)->next->type == WORD)
	{
		cmd->heredoc = ft_strdup((*token)->next->value);
		if (cmd->heredoc == NULL)
			return (-1);
		(*token) = (*token)->next;
	}
	return (0);
}

int	process_token(t_command *cmd, t_token **token, int *i)
{
	if ((*token)->type == WORD)
	{
		cmd->args[*i] = ft_strdup((*token)->value);
		if (cmd->args[*i] == NULL)
			return (-1);
		(*i)++;
	}
	else if (!(*token)->next || (*token)->next->type != WORD)
		return (-2);
	else if (process_special_token(cmd, token) == -1)
		return (-1);
	return (0);
}
