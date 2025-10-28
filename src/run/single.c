/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:40:28 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 16:41:53 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "parser.h"
#include "run.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void	parent_builtin_redirs(t_command *cmd, int heredoc_fd, int *saved_in,
		int *saved_out)
{
	*saved_in = -1;
	*saved_out = -1;
	if (cmd->infile || heredoc_fd != -1)
		*saved_in = dup(STDIN_FILENO);
	if (cmd->outfile)
		*saved_out = dup(STDOUT_FILENO);
	if (cmd->infile)
		apply_in_redir(cmd);
	if (heredoc_fd != -1)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(heredoc_fd);
	}
	if (cmd->outfile)
		apply_out_redir(cmd);
}

static t_single_res	single_try_builtin(t_command *cmd, t_node *env)
{
	t_single_res	res;
	int				saved_in;
	int				saved_out;

	res.hd_fd = -1;
	if (cmd->heredoc)
		res.hd_fd = collect_heredoc(cmd->heredoc);
	if (cmd->args)
		res.is_builtin = is_b_in(cmd->args[0]);
	if (res.is_builtin)
	{
		parent_builtin_redirs(cmd, res.hd_fd, &saved_in, &saved_out);
		res.status = run_builtin(cmd->args, env);
		g_exit_code = res.status;
		restore_stdio(saved_in, saved_out);
		res.hd_fd = -1;
	}
	else
		res.status = 0;
	return (res);
}

static int	fork_and_exec_external(t_command *cmd, t_node *env, int hd_fd,
		char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(path), close(hd_fd), 84);
	if (pid == 0)
	{
		if (apply_redirections(cmd, hd_fd) == -1)
			exit(1);
		reset_signals();
		execve(path, cmd->args, stringify(env));
		perror(cmd->args[0]);
		exit(127);
	}
	free(path);
	if (hd_fd != -1)
		close(hd_fd);
	waitpid(pid, &status, 0);
	handle_status(status);
	return (1);
}

static int	run_single_external(t_command *cmd, t_node *env, int hd_fd)
{
	char	*path;

	path = find_bin(cmd->args, env);
	if (path == NULL)
		return (cmd_not_found(cmd->args[0]), 1);
	return (fork_and_exec_external(cmd, env, hd_fd, path));
}

int	handle_single(t_command *commands, t_node *env)
{
	t_single_res	r;

	if (commands->args == NULL)
		return (0);
	r = single_try_builtin(commands, env);
	if (r.is_builtin)
		return (r.status);
	return (run_single_external(commands, env, r.hd_fd));
}
