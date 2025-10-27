/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:08 by mmicael           #+#    #+#             */
/*   Updated: 2025/10/27 15:44:12 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "shell.h"
#include "utils.h"

int	ft_echo(char **args, t_node *env)
{
	int	i;
	int	newline;

	(void)env;
	i = 1;
	newline = 0;
	if (args[i] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline == 0)
		printf("\n");
	return (0);
}
