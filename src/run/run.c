/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:57 by tonio             #+#    #+#             */
/*   Updated: 2025/10/22 20:13:00 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"
#include <errno.h>
#include <signal.h>

static int	handle_child(char *path_to_bin, char **args, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(path_to_bin, args, env) == -1)
	{
		perror(args[0]);
		exit(127);
	}
	return (0);
}

static int	handle_status(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGSEGV)
		{
			write(2, "Segmentation fault", 19);
			if (WCOREDUMP(status))
				write(2, " (core dumped)", 14);
			write(2, "\n", 1);
		}
		else if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
	}
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_code = 128 + WTERMSIG(status);
	return (1);
}

int	create_fork_and_run(char *path_to_bin, char **args, char **env)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (84);
	}
	if (pid == 0)
		handle_child(path_to_bin, args, env);
	waitpid(pid, &status, 0);
	exit_code = handle_status(status);
	return (exit_code);
}

int	run_bin(char *cmd, char **args, char **env)
{
	create_fork_and_run(cmd, args, env);
	return (1);
}
