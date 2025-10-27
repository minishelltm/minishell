/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:51 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 13:57:37 by ande-vat         ###   ########.fr       */
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
		exit(0);
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
			write(1, "exit\n", 6);
			break ;
		}
		if (is_blank_line(line))
			continue ;
		add_history(line);
		interrupt = shell_loop(&args, env, line);
		free(line);
	}
	return (0);
}
