/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:41:59 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 03:49:39 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"
#include <signal.h>
#include <readline/readline.h>

static void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		close(0);
		write(1, "\n", 1);
	}
}

static void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

static int	heredoc_loop(int write_fd, const char *delim)
{
	char	*line;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	setup_heredoc_signals();
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			dup2(stdin_copy, STDIN_FILENO);
			close(stdin_copy);
			setup_signals();
			return (1);
		}
		if (ft_strncmp(line, (char *)delim, 0) == 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(stdin_copy);
	setup_signals();
	return (0);
}

int	collect_heredoc(const char *delim)
{
	int	hd[2];
	int	ret;

	if (pipe(hd) == -1)
		return (perror("pipe"), -1);
	ret = heredoc_loop(hd[1], delim);
	close(hd[1]);
	if (ret)
	{
		close(hd[0]);
		return (-1);
	}
	return (hd[0]);
}
