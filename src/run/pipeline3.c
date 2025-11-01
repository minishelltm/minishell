/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:13:55 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 03:53:12 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "run.h"
#include "shell.h"

void	restore_stdin(int saved)
{
	if (saved != -1)
	{
		dup2(saved, STDIN_FILENO);
		close(saved);
	}
}

int	open_pipe_if_needed(t_pipeline *pl, int has_next)
{
	if (has_next)
	{
		if (pipe(pl->pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

int	pipeline_init(t_pipeline *pl, t_node *env, t_command *cmds)
{
	pl->env = env;
	pl->prev_fd = -1;
	pl->pcount = 0;
	pl->count = count_commands(cmds);
	pl->heredocs = NULL;
	if (pl->count > 0)
		pl->heredocs = prepare_heredocs(cmds, pl->count);
	if (pl->count > 0 && pl->heredocs == NULL)
		return (-1);
	pl->pids = NULL;
	if (pl->count > 0)
		pl->pids = malloc(sizeof(pid_t) * pl->count);
	if (pl->count > 0 && pl->pids == NULL)
		return (-1);
	return (0);
}
