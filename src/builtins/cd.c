/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:39:28 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:46:07 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "shell.h"
#include "utils.h"

int	ft_cd(char **args, t_node *env)
{
	int		retval;
	char	*oldpwd;

	retval = -404;
	oldpwd = getcwd(NULL, 0);
	if (args[2] != NULL)
	{
		write(2, "cd: Too many arguments.\n", 23);
		return (0);
	}
	if (args[1] != NULL && ft_strncmp(args[1], "-", 0) == 0)
		retval = chdir(find_node(env, "OLDPWD=")->data.value);
	if (args[1] == NULL)
		retval = chdir("/home");
	if (args[1] != NULL && ft_strncmp(args[1], "~", 0) == 0)
		retval = chdir("/home");
	if (args[1] != NULL && ft_strncmp(args[1], "/", 0) == 0)
		retval = chdir("/");
	if (args[1] != NULL)
		retval = chdir(args[1]);
	if (retval == 0)
		update_env("OLDPWD=", oldpwd, env);
	return (retval);
}
