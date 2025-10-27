/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:40:28 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 08:34:18 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "run.h"
#include "parser.h"
#include "envify.h"

static void	parent_builtin_redirs(t_command *cmd, int heredoc_fd, int *saved)
{
	int	out_fd;

	*saved = -1;
	if (cmd->infile)
		apply_in_redir(cmd);
	if (heredoc_fd != -1)
	{
		*saved = dup(STDIN_FILENO);
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(heredoc_fd);
	}
	out_fd = -1;
	if (cmd->outfile)
		apply_out_redir(cmd);
	(void)out_fd;
}

static t_single_res	single_try_builtin(t_command *cmd, t_node *env)
{
	t_single_res	res;
	int				saved;

	res.hd_fd = -1;
	if (cmd->heredoc)
		res.hd_fd = collect_heredoc(cmd->heredoc);
	res.status = run_builtin(cmd->args, env);
	res.is_builtin = (res.status != 404);
	if (res.is_builtin)
	{
		parent_builtin_redirs(cmd, res.hd_fd, &saved);
		g_exit_code = res.status;
		restore_stdin(saved);
	}
	return (res);
}

static int	fork_and_exec_external(t_command *cmd, t_node *env,
	int hd_fd, char *path)
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

	if (find_node(env, "PATH=") == NULL)
		return (cmd_not_found(cmd->args[0]), 1);
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
	if (find_node(env, "PATH=") == NULL)
		return (cmd_not_found(commands->args[0]), 1);
	return (run_single_external(commands, env, r.hd_fd));
}
