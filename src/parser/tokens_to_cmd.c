/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:13:57 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 05:38:47 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	return (cmd);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	if (cmd->next != NULL)
		free_command(cmd->next);
	if (cmd->args != NULL)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->infiles != NULL)
		free_arr(cmd->infiles);
	if (cmd->outfiles != NULL)
		free_arr(cmd->outfiles);
	if (cmd->heredoc != NULL)
		free(cmd->heredoc);
	free(cmd);
}

int	alloc_args(t_command *cmd, t_allocinfo allocinfo)
{
	int	malloc_fail;

	malloc_fail = 0;
	cmd->args = ft_calloc(sizeof(char *), allocinfo.nb_args + 1);
	if (cmd->args == NULL)
		return (-1);
	cmd->args[allocinfo.nb_args] = NULL;
	if (allocinfo.nb_infiles > 0)
	{
		cmd->infiles = ft_calloc(sizeof(char *), allocinfo.nb_infiles + 1);
		if (cmd->infiles == NULL)
			malloc_fail = 1;
	}
	if (allocinfo.nb_outfiles > 0)
	{
		cmd->outfiles = ft_calloc(sizeof(char *), allocinfo.nb_outfiles + 1);
		if (cmd->outfiles == NULL)
			malloc_fail = 1;
	}
	if (malloc_fail == 1)
		return (free(cmd->args), free(cmd->infiles), free(cmd->outfiles), -1);
	return (0);
}

int	fill_command(t_command *cmd, t_token **token)
{
	int	i;
	int	res;

	i = 0;
	while (*token && (*token)->type != PIPE)
	{
		res = process_token(cmd, token, &i);
		if (res < 0)
			return (res);
		*token = (*token)->next;
	}
	if (*token && (*token)->type == PIPE)
	{
		*token = (*token)->next;
	}
	return (0);
}

t_command	*token_to_cmd(t_token *tokens)
{
	t_token		*token;
	t_command	*cmd;
	t_command	*cmd_head;
	t_allocinfo	allocinfo;

	cmd_head = init_command();
	if (cmd_head == NULL)
		return (NULL);
	cmd = cmd_head;
	token = tokens;
	while (token != NULL)
	{
		allocinfo = count_args_cmd(token);
		if (alloc_args(cmd, allocinfo) == -1)
			return (free_command(cmd_head), NULL);
		if (fill_command(cmd, &token) == -1)
			return (free_command(cmd_head), NULL);
		if (token)
		{
			cmd->next = init_command();
			cmd = cmd->next;
		}
	}
	return (cmd_head);
}
