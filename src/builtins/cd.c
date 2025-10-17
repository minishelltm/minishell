/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:39:28 by tonio             #+#    #+#             */
/*   Updated: 2025/10/17 17:01:58 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "shell.h"
#include "utils.h"

int	ft_cd(char **args, t_node *env)
{
	int		retval;
	char	*oldpwd;
	char	*home;
	char	*path;

	retval = -404;
	oldpwd = getcwd(NULL, 0);
	if (args[2] != NULL)
	{
		write(2, "cd: Too many arguments.\n", 23);
		return (0);
	}
	if (args[1] == NULL)
		retval = chdir(find_node(env, "HOME=")->data.value);
	else if (ft_strncmp(args[1], "-", 0) == 0)
		retval = chdir(find_node(env, "OLDPWD=")->data.value);
	else if (ft_strncmp(args[1], "/", 0) == 0)
		retval = chdir("/");
	else if (args[1][0] == '~')
	{
		home = find_node(env, "HOME=")->data.value;
		if (args[1][1] == '\0')
			path = ft_strdup(home);
		else
			path = ft_strjoin(home, args[1] + 1);
		retval = chdir(path);
		free(path);
	}
	else
		retval = chdir(args[1]);
	if (retval == 0)
		update_env("OLDPWD=", oldpwd, env);
	return (retval);
}
