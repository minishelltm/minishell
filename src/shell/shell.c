/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:51 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 06:21:34 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "list.h"
#include "run.h"
#include "shell.h"
#include "utils.h"
#include <dirent.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!is_ws(line[i]))
			return (0);
		i++;
	}
	if (line[0])
		add_history(line);
	free(line);
	return (1);
}

static int	shell_loop(char ***args, t_node *env, char *line)
{
	int			interrupt;
	t_command	*commands;

	(void)args;
	interrupt = 0;
	commands = NULL;
	commands = parse_input(line, env);
	if (commands == NULL)
		return (0);
	interrupt = run_commands(commands, env);
	if (interrupt == 255)
	{
		free_command(commands);
		return (255);
	}
	free_command(commands);
	return (interrupt);
}

int	shell(t_node *env)
{
	char	*line;
	char	**args;
	int		interrupt;

	args = NULL;
	interrupt = 0;
	while (1)
	{
		if (interrupt == 255)
			break ;
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (is_blank_line(line))
			continue ;
		add_history(line);
		interrupt = shell_loop(&args, env, line);
		free(line);
	}
	return (g_exit_code);
}
