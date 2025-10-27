/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:52:00 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 08:35:39 by tonio            ###   ########.fr       */
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

	if (!cmd->infile)
		return (0);
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
		return (perror(cmd->infile), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), close(fd), -1);
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

	if (!cmd->outfile)
		return (0);
	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(cmd->outfile), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(fd), -1);
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
