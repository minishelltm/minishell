/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:39:14 by tonio             #+#    #+#             */
/*   Updated: 2025/10/15 18:33:40 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envify.h"
#include "shell.h"
#include "utils.h"
#include <errno.h>

static int	check_env_key(char *key)
{
	if (!((key[0] >= 'a' && key[0] <= 'z') || (key[0] >= 'A' && key[0] <= 'Z')))
	{
		write(2, "setenv: Variable name must begin with a letter.\n", 48);
		return (1);
	}
	if (!is_alphanum(key, ALPHANUM))
	{
		write(2,
			"setenv: Variable name must contain alphanumeric characters.\n",
			61);
		return (1);
	}
	return (0);
}

int	myenv(t_node *env)
{
	char	**envarr;
	int		i;

	envarr = stringify(env);
	i = 0;
	while (envarr[i] != NULL)
	{
		write(1, envarr[i], ft_strlen(envarr[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	mysetenv(char **args, t_node *env)
{
	char	*key;

	key = NULL;
	if (args[1] == NULL)
		return (myenv(env));
	if (check_env_key(args[1]) != 0)
	{
		return (1);
	}
	if (args[2] != NULL && args[3] == NULL)
	{
		key = ft_strcat(args[1], "=");
		env = update_env(key, args[2], env);
		return (0);
	}
	if (args[2] == NULL)
	{
		key = ft_strcat(args[1], "=");
		env = update_env(key, ft_strdup(""), env);
		return (0);
	}
	write(2, "setenv: Too many arguments.\n", 26);
	return (0);
}

int	myunsetenv(char **args, t_node *env)
{
	t_node	*del;
	int		i;

	i = 1;
	del = NULL;
	if (args[1] == NULL)
	{
		write(2, "unsetenv: Too few arguments.\n", 29);
	}
	while (args[i] != NULL)
	{
		del = find_node(env, (ft_strcat(args[i], "=")));
		if (del != NULL)
			delete_node(env, del);
		++i;
	}
	return (0);
}

int	run_builtin(char **args, t_node *env)
{
	int	status;

	status = 404;
	if (ft_strncmp(args[0], "unsetenv", 0) == 0)
		return (myunsetenv(args, env));
	if (ft_strncmp(args[0], "cd", 0) == 0)
	{
		status = ft_cd(args, env);
		if (status != 0 && errno != ENOTDIR)
			perror(args[1]);
		if (status != 0 && errno == ENOTDIR)
		{
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": Not a directory.\n", 20);
		}
	}
	if (ft_strncmp(args[0], "env", 0) == 0)
		return (myenv(env));
	if (ft_strncmp(args[0], "setenv", 0) == 0)
		return (mysetenv(args, env));
	if (ft_strncmp(args[0], "exit", 0) == 0)
		return (255);
	return (status);
}
