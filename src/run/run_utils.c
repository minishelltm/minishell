/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:39:38 by ande-vat          #+#    #+#             */
/*   Updated: 2025/10/27 16:43:52 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "parser.h"
#include "run.h"
#include "shell.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	is_b_in(char *name)
{
	if (ft_strncmp(name, "cd", 0) == 0
		|| ft_strncmp(name, "echo", 0) == 0
		|| ft_strncmp(name, "exit", 0) == 0
		|| ft_strncmp(name, "pwd", 0) == 0
		|| ft_strncmp(name, "env", 0) == 0
		|| ft_strncmp(name, "export", 0) == 0
		|| ft_strncmp(name, "unset", 0) == 0)
		return (1);
	return (0);
}

void	restore_stdio(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		if (dup2(saved_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(saved_in);
	}
	if (saved_out != -1)
	{
		if (dup2(saved_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(saved_out);
	}
}
