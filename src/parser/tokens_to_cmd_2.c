/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:13:57 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 05:50:58 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

t_allocinfo	count_args_cmd(t_token *token)
{
	t_allocinfo	ret;
	t_token		*tmp;

	tmp = token;
	ret.nb_args = 0;
	ret.nb_infiles = 0;
	ret.nb_outfiles = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN)
		{
			ret.nb_infiles++;
			tmp = tmp->next;
		}
		else if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			ret.nb_outfiles++;
			tmp = tmp->next;
		}
		else if (tmp->type == WORD)
			ret.nb_args++;
		tmp = tmp->next;
	}
	return (ret);
}

int	process_special_token(t_command *cmd, t_token **token)
{
	if ((*token)->type == REDIR_IN && (*token)->next->type == WORD)
	{
		cmd->infiles[cmd->nb_infiles] = ft_strdup((*token)->next->value);
		if (cmd->infiles[cmd->nb_infiles] == NULL)
			return (-1);
		cmd->nb_infiles++;
	}
	else if (((*token)->type == REDIR_OUT || (*token)->type == APPEND)
		&& (*token)->next->type == WORD)
	{
		cmd->outfiles[cmd->nb_outfiles] = ft_strdup((*token)->next->value);
		if (cmd->outfiles[cmd->nb_outfiles] == NULL)
			return (-1);
		cmd->append = ((*token)->type == APPEND);
		cmd->nb_outfiles++;
	}
	else if ((*token)->type == HEREDOC && (*token)->next->type == WORD)
	{
		cmd->heredoc = ft_strdup((*token)->next->value);
		if (cmd->heredoc == NULL)
			return (-1);
	}
	(*token) = (*token)->next;
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
