/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 07:41:59 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 08:37:46 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"

static int	heredoc_loop(int write_fd, const char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, (char *)delim, 0) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	collect_heredoc(const char *delim)
{
	int	hd[2];

	if (pipe(hd) == -1)
		return (perror("pipe"), -1);
	heredoc_loop(hd[1], delim);
	close(hd[1]);
	return (hd[0]);
}
