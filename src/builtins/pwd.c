/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:11 by mmicael           #+#    #+#             */
/*   Updated: 2025/10/27 14:45:27 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "shell.h"
#include "utils.h"

int	ft_pwd(char **args, t_node *env)
{
	char	*cwd;

	(void)args;
	(void)env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
