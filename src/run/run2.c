/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:43:18 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 20:49:31 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "utils.h"

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	cmd_not_found(char *name)
{
	write(2, name, ft_strlen(name));
	write(2, ": Command not found.\n", 22);
	g_exit_code = 127;
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	handle_child(char *path_to_bin, char **args, char **env)
{
	reset_signals();
	if (execve(path_to_bin, args, env) == -1)
	{
		perror(args[0]);
		exit(127);
	}
	return (0);
}

int	handle_status(int status)
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
