/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:57 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 04:08:04 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"
#include <errno.h>
#include <signal.h>
#include "parser.h"
#include "builtins.h"
#include "envify.h"
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "run.h"

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

int	run_commands(t_command *commands, t_node *env)
{
	if (commands == NULL)
		return (0);
	if (commands->next == NULL)
		return (handle_single(commands, env));
	return (run_pipeline(commands, env));
}
