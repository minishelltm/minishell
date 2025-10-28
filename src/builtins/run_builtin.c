/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:39:14 by tonio             #+#    #+#             */
/*   Updated: 2025/10/28 19:35:52 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envify.h"
#include "shell.h"
#include "utils.h"
#include <errno.h>

int	myunsetenv(char **args, t_node *env)
{
	t_node	*del;
	int		i;
	char	*with_eq;

	i = 1;
	del = NULL;
	if (args[1] == NULL)
	{
		write(2, "unset: Too few arguments.\n", 27);
	}
	while (args[i] != NULL)
	{
		with_eq = ft_strcat(args[i], "=");
		del = find_node(env, with_eq);
		if (del != NULL)
			delete_node(env, del);
		i++;
		free(with_eq);
	}
	return (0);
}

int	is_exit(char **args, int status)
{
	if (ft_strncmp(args[0], "exit", 0) == 0)
	{
		write(1, "exit\n", 6);
		if (args[1] && is_alphanum(args[1], NUM))
			g_exit_code = ft_atoi(args[1]);
		else if (args[1])
		{
			write(2, "exit: numeric argument required\n", 33);
			g_exit_code = 2;
			return (255);
		}
		if (args[1] && args[2])
		{
			write(2, "exit: too many arguments\n", 26);
			return (1);
		}
		return (255);
	}
	return (status);
}

int	run_builtin(char **args, t_node *env)
{
	int	status;

	status = 404;
	if (ft_strncmp(args[0], "unset", 0) == 0)
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
	if (ft_strncmp(args[0], "export", 0) == 0)
		return (ft_export(args, env));
	if (ft_strncmp(args[0], "pwd", 0) == 0)
		return (ft_pwd(args, env));
	if (ft_strncmp(args[0], "echo", 0) == 0)
		return (ft_echo(args, env));
	return (is_exit(args, status));
}
