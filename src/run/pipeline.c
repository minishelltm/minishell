/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:10:13 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 05:39:52 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "parser.h"
#include "shell.h"

static void	free_pipeline(t_pipeline *pl)
{
	free(pl->pids);
	free(pl->heredocs);
}

static int	fork_one(t_pipeline *pl, t_command *cmd, int heredoc_fd)
{
	pl->pids[pl->pcount] = fork();
	if (pl->pids[pl->pcount] == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pl->pids[pl->pcount] == 0)
		child_exec_command(cmd, pl, heredoc_fd, cmd->next != NULL);
	return (0);
}

static int	process_commands(t_pipeline *pl, t_command *cmds)
{
	t_command	*cmd;
	int			i;
	int			hfd;
	int			has_next;

	cmd = cmds;
	i = 0;
	while (cmd != NULL)
	{
		has_next = (cmd->next != NULL);
		if (open_pipe_if_needed(pl, has_next) == -1)
			return (-1);
		hfd = -1;
		if (pl->heredocs != NULL)
			hfd = pl->heredocs[i];
		if (fork_one(pl, cmd, hfd) == -1)
			return (-1);
		parent_after_fork(pl, has_next);
		if (pl->heredocs != NULL && pl->heredocs[i] != -1)
			close(pl->heredocs[i]);
		pl->pcount += 1;
		i += 1;
		cmd = cmd->next;
	}
	return (0);
}

static void	wait_children(t_pipeline *pl)
{
	int	i;
	int	status;

	i = 0;
	while (i < pl->pcount)
	{
		waitpid(pl->pids[i], &status, 0);
		handle_status(status);
		i += 1;
	}
}

int	run_pipeline(t_command *commands, t_node *env)
{
	t_pipeline	pl;

	if (pipeline_init(&pl, env, commands) == -1)
		return (1);
	if (process_commands(&pl, commands) == -1)
	{
		free_pipeline(&pl);
		return (1);
	}
	wait_children(&pl);
	free_pipeline(&pl);
	return (1);
}
