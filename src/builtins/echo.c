/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:08 by mmicael           #+#    #+#             */
/*   Updated: 2025/10/28 13:02:29 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "shell.h"
#include "utils.h"

int	is_dashn(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, t_node *env)
{
	int	i;
	int	newline;

	(void)env;
	i = 1;
	newline = 0;
	while (args[i] && is_dashn(args[i]))
	{
		newline = 1;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] && args[i][0])
			write(1, " ", 1);
		i++;
	}
	if (newline == 0)
		write(1, "\n", 1);
	return (0);
}
