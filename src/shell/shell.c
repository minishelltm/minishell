/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:51 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:55:32 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// FIX OMG
#include "envify.h"
#include "list.h"
#include "run.h"
#include "shell.h"
#include "utils.h"
#include <dirent.h>
#include <sys/stat.h>

static char	is_dot(char *name)
{
	if (ft_strncmp(name, ".", 0) == 0)
		return (1);
	if (ft_strncmp(name, "..", 0) == 0)
		return (1);
	return (0);
}

static char	*find_loop(DIR *d, struct dirent *dirent, char *name, char *path)
{
	char		*full_path;
	char		*bin_path;
	struct stat	st;

	full_path = NULL;
	bin_path = NULL;
	while (dirent != NULL)
	{
		if (bin_path != NULL)
			break ;
		if (ft_strncmp(dirent->d_name, name, 0) == 0)
			bin_path = ft_pathcat(path, dirent->d_name);
		if (is_dot(dirent->d_name) == 1)
		{
			dirent = readdir(d);
			continue ;
		}
		full_path = ft_pathcat(path, dirent->d_name);
		if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode))
			bin_path = find_bin_path(full_path, name);
		dirent = readdir(d);
		free(full_path);
	}
	return (bin_path);
}

char	*find_bin_path(char *path, char *name)
{
	char			*bin_path;
	DIR				*d;
	struct dirent	*dirent;

	bin_path = NULL;
	d = opendir(path);
	if (d == NULL)
		return (NULL);
	dirent = readdir(d);
	bin_path = find_loop(d, dirent, name, path);
	closedir(d);
	return (bin_path);
}

int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*find_bin(char **args, t_node *env)
{
	t_node	*pathnode;
	char	*paths;
	char	*test_path;
	char	*bin_path;

	pathnode = find_node(env, "PATH=");
	paths = ft_strdup(pathnode->data.value);
	test_path = NULL;
	bin_path = NULL;
	if (has_slash(args[0]) == 1)
		return (args[0]);
	if (paths == NULL)
	{
		return (NULL);
	}
	test_path = strtok(paths, ":");
	while (test_path != NULL)
	{
		bin_path = find_bin_path(test_path, args[0]);
		if (bin_path != NULL)
			break ;
		test_path = strtok(NULL, ":");
	}
	return (bin_path);
}

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

	interrupt = 0;
	commands = NULL;
	line[ft_strlen(line) - 1] = '\0';
	if (line[0] == 4)
		exit(0);
	commands = parse_semicolon(line); // FIX OMG
	for (int i = 0; commands[i] != NULL; i++)
	{
		interrupt = shell_more_loop(args, env, commands[i]);
		if (interrupt == 255)
			exit(0);
	}
	free(commands);
	return (interrupt);
}

int	shell(t_node *env)
{
	char	*line;
	char	**args;
	size_t	lsize;
	int		size;
	int		interrupt;

	line = NULL;
	args = (char **){NULL};
	lsize = 0;
	size = 0;
	interrupt = 0;
	while (1)
	{
		if (interrupt == 255)
			break ;
		write(1, "$> ", 3);
		size = getline(&line, &lsize, stdin);
		if (size == -1)
			exit(0);
		if (ft_strncmp(line, "\n", 0) == 0)
			continue ;
		interrupt = shell_loop(&args, env, line);
		lsize = 0;
	}
	return 0;
}
