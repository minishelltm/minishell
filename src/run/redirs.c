/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:52:00 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 05:45:39 by tonio            ###   ########.fr       */
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

int	apply_in_redir(t_command *cmd)
{
	int	fd;
	int	i;

	if (!cmd->infiles || cmd->nb_infiles <= 0)
		return (0);
	i = 0;
	while (i < cmd->nb_infiles)
	{
		fd = open(cmd->infiles[i], O_RDONLY);
		if (fd == -1)
			return (perror(cmd->infiles[i]), -1);
		if (i < cmd->nb_infiles - 1)
			close(fd);
		else if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close(fd), -1);
		i++;
	}
	if (fd != -1)
		close(fd);
	return (0);
}

int	apply_heredoc_redir(int heredoc_fd)
{
	if (heredoc_fd == -1)
		return (0);
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
		return (perror("dup2"), close(heredoc_fd), -1);
	close(heredoc_fd);
	return (0);
}

int	apply_out_redir(t_command *cmd)
{
	int	fd;
	int	i;

	if (!cmd->outfiles || cmd->nb_outfiles <= 0)
		return (0);
	i = 0;
	while (i < cmd->nb_outfiles)
	{
		if (cmd->append)
			fd = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(cmd->outfiles[i]), -1);
		if (i < cmd->nb_outfiles - 1)
			close(fd);
		else if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), close(fd), -1);
		i++;
	}
	if (fd != -1)
		close(fd);
	return (0);
}

int	apply_redirections(t_command *cmd, int heredoc_fd)
{
	if (apply_in_redir(cmd) == -1)
		return (-1);
	if (apply_heredoc_redir(heredoc_fd) == -1)
		return (-1);
	if (apply_out_redir(cmd) == -1)
		return (-1);
	return (0);
}
