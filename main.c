/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:39 by tonio             #+#    #+#             */
/*   Updated: 2025/10/22 20:11:57 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "list.h"
#include "shell.h"
#include "utils.h"
#include <signal.h>

volatile sig_atomic_t g_exit_code = 0;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n$> ", 4);
	return ;
}

void	setup_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	clean_oldpwd(t_node *list)
{
	update_env("OLDPWD=", ft_strdup(""), list);
}

int	main(int ac, char **av, char **env)
{
	int		retval;
	t_node	*list;

	retval = 0;
	list = envify(env);
	clean_oldpwd(list);
	signal(SIGINT, sig_handler);
	if (ac != 1 || av[1] != NULL)
	{
		return (84);
	}
	retval = shell(list);
	free_list(list);
	return (retval);
}
