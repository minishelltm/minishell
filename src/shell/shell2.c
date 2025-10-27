/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:24:23 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 11:02:31 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			bin_path = (free(bin_path), find_bin_path(full_path, name));
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
	int		i;

	i = 0;
	pathnode = find_node(env, "PATH=");
	paths = ft_strdup(pathnode->data.value);
	test_path = NULL;
	bin_path = NULL;
	if (has_slash(args[0]) == 1)
		return (args[0]);
	if (paths == NULL)
		return (NULL);
	test_path = split_path(paths, i);
	while (test_path != NULL)
	{
		bin_path = find_bin_path(test_path, args[0]);
		if (bin_path != NULL)
			break ;
		i++;
		test_path = (free(test_path), split_path(paths, i));
	}
	return (free(paths), free(test_path), bin_path);
}
