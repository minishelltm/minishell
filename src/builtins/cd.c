/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:39:28 by tonio             #+#    #+#             */
/*   Updated: 2025/11/01 00:06:31 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "shell.h"
#include "utils.h"

static int	home_logic(char *args, t_node *env)
{
	char	*home;
	char	*path;
	int		retval;

	home = find_node(env, "HOME=")->data.value;
	if (args[1] == '\0')
		path = ft_strdup(home);
	else
		path = ft_strjoin(home, args + 1);
	retval = chdir(path);
	free(path);
	return (retval);
}

void	update_pwd(char *oldpwd, t_node *env)
{
	update_env("OLDPWD=", oldpwd, env);
	update_env("PWD=", getcwd(NULL, 0), env);
}

int	ft_cd(char **args, t_node *env)
{
	int		retval;
	char	*oldpwd;

	retval = -404;
	if (args[1] && args[2])
	{
		write(2, "cd: Too many arguments.\n", 25);
		return (0);
	}
	oldpwd = getcwd(NULL, 0);
	if (args[1] == NULL)
		retval = chdir(find_node(env, "HOME=")->data.value);
	else if (ft_strncmp(args[1], "-", 0) == 0)
		retval = chdir(find_node(env, "OLDPWD=")->data.value);
	else if (ft_strncmp(args[1], "/", 0) == 0)
		retval = chdir("/");
	else if (args[1][0] == '~')
		retval = home_logic(args[1], env);
	else
		retval = chdir(args[1]);
	if (retval == 0)
		update_pwd(oldpwd, env);
	else
		free(oldpwd);
	return (retval);
}
