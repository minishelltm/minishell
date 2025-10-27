/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:11:00 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 08:29:31 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "parser.h"
#include "shell.h"
#include "envify.h"

int	*prepare_heredocs(t_command *cmds, int count)
{
	int			*arr;
	int			i;
	t_command	*tmp;

	arr = malloc(sizeof(int) * count);
	if (arr == NULL)
		return (NULL);
	i = 0;
	tmp = cmds;
	while (i < count)
	{
		arr[i] = -1;
		if (tmp != NULL && tmp->heredoc != NULL)
			arr[i] = collect_heredoc(tmp->heredoc);
		if (tmp != NULL)
			tmp = tmp->next;
		i += 1;
	}
	return (arr);
}

static void	child_setup_pipes(int prev_fd, int has_next, int pipe_fd[2])
{
	if (prev_fd != -1 && dup2(prev_fd, STDIN_FILENO) == -1)
		perror("dup2");
	if (has_next && dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	if (pipe_fd[0] > 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] > 0)
		close(pipe_fd[1]);
	if (prev_fd > 0)
		close(prev_fd);
}

static void	exec_external(char **args, t_node *env)
{
	char	*path;

	if (find_node(env, "PATH=") == NULL)
	{
		cmd_not_found(args[0]);
		exit(127);
	}
	path = find_bin(args, env);
	if (path == NULL)
	{
		cmd_not_found(args[0]);
		exit(127);
	}
	execve(path, args, stringify(env));
	perror(args[0]);
	exit(127);
}

void	child_exec_command(t_command *cmd, t_pipeline *pl,
		int heredoc_fd, int has_next)
{
	child_setup_pipes(pl->prev_fd, has_next, pl->pipe_fd);
	if (apply_redirections(cmd, heredoc_fd) == -1)
		exit(1);
	if (cmd->args != NULL && run_builtin(cmd->args, pl->env) != 404)
		exit(g_exit_code);
	exec_external(cmd->args, pl->env);
}

void	parent_after_fork(t_pipeline *pl, int has_next)
{
	if (pl->prev_fd != -1)
		close(pl->prev_fd);
	if (has_next)
	{
		close(pl->pipe_fd[1]);
		pl->prev_fd = pl->pipe_fd[0];
	}
	else
		pl->prev_fd = -1;
}
