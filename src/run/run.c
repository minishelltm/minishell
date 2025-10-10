/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:57 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:45:45 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"
#include <errno.h>
#include <signal.h>

static char	*get_bin_name(char *path_to_bin)
{
	char	*cpy;
	char	*retval;
	char	*token;

	cpy = ft_strdup(path_to_bin);
	retval = NULL;
	token = strtok(cpy, "/");
	while (token != NULL)
	{
		retval = ft_strdup(token);
		token = strtok(NULL, "/");
	}
	free(cpy);
	return (retval);
}

static int	run_bin_with_path(char *path_to_bin, char **args, char **env)
{
	char	*errstring;

	if (execve(path_to_bin, args, env) == -1)
	{
		errstring = strerror(errno);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": ", 2);
		write(2, errstring, ft_strlen(errstring));
		if (errno == ENOEXEC)
			write(2, ". Wrong Architecture", 20);
		write(2, ".", 1);
		write(2, "\n", 1);
		return (84);
	}
	exit(0);
	return (0);
}

void	segfault(int status)
{
	write(2, "Segmentation fault", 19);
	if (__WCOREDUMP(status))
		write(2, " (core dumped)", 14);
	write(2, "\n", 1);
}

static int	create_fork_and_run(char *path_to_bin, char **args, char **env)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("fork");
		return (84);
	}
	if (pid == 0)
	{
		if (run_bin_with_path(path_to_bin, args, env) == 84)
			exit(84);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror(get_bin_name(path_to_bin));
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
			segfault(status);
	}
	return (0);
}

int	run_bin(char *cmd, char **args, char **env)
{
	create_fork_and_run(cmd, args, env);
	return (1);
}
