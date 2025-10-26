/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:39 by tonio             #+#    #+#             */
/*   Updated: 2025/10/26 19:30:46 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "list.h"
#include "shell.h"
#include "utils.h"
#include <signal.h>
#include "parser.h"


volatile sig_atomic_t g_exit_code = 0;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\nminishell$", 12);
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

/*
// test parsing
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char		*line;
	int			interrupt;
	t_command	*cmds;
	t_node	*list;

	list = envify(envp);
	clean_oldpwd(list);
	interrupt = 0;
	while (1)
	{
		if (interrupt == 255)
			break ;
		line = readline("minishell$ ");
		if (!line)
			exit(0);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		cmds = parse_input(line, list);
		print_cmds(cmds);
		free(line);
	}
	return (0);
} */