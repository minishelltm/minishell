/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:51 by tonio             #+#    #+#             */
/*   Updated: 2025/10/18 16:41:39 by tonio            ###   ########.fr       */
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

static int	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Command not found.\n", 22);
	return (1);
}

int	shell_more_loop(char ***args, t_node *env, char *line)
{
	int		interrupt;
	char	*path_to_bin;

	interrupt = 0;
	path_to_bin = NULL;
	*args = ft_str_to_word_array(line);
	if (*args == NULL)
		return (0);
	if (includes(line, '|') == 1)
		return (0);
	free(line);
	interrupt = run_builtin(*args, env);
	if (interrupt == 404)
	{
		if (find_node(env, "PATH=") != NULL)
			path_to_bin = find_bin(*args, env);
		if (path_to_bin == NULL)
			return (cmd_not_found(*(args)[0]));
		interrupt = run_bin(path_to_bin, *args, stringify(env));
		free(path_to_bin);
	}
	return (interrupt);
}

static int	shell_loop(char ***args, t_node *env, char *line)
{
	int		interrupt;
	char	**commands;
	int		i;

	i = 0;
	interrupt = 0;
	commands = NULL;
	commands = parse_semicolon(line);
	while (commands[i] != NULL)
	{
		interrupt = shell_more_loop(args, env, commands[i]);
		if (interrupt == 255)
			exit(0); // Handle exit better
		i++;
	}
	free(commands);
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
			exit(0);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		interrupt = shell_loop(&args, env, line);
		free(line);
	}
	return (0);
}
