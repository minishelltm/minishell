/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:39 by tonio             #+#    #+#             */
/*   Updated: 2025/10/29 17:18:08 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "list.h"
#include "shell.h"
#include "utils.h"
#include <signal.h>
#include "parser.h"

volatile sig_atomic_t	g_exit_code = 0;

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

void	update_shlvl(t_node *list)
{
	t_node	*shlvl;
	int		val;

	val = 0;
	shlvl = find_node(list, "SHLVL=");
	if (shlvl != NULL && is_alphanum(shlvl->data.value, NUM))
		val = ft_atoi(shlvl->data.value);
	val += 1;
	if (val >= 10000)
		val = 1;
	update_env("SHLVL=", ft_itoa(val), list);
}

void	clean_oldenv(t_node *list)
{
	update_env("OLDPWD=", ft_strdup(""), list);
	update_env("PWD=", getcwd(NULL, 0), list);
	update_shlvl(list);
}

int	main(int ac, char **av, char **env)
{
	int		retval;
	t_node	*list;

	retval = 0;
	list = envify(env);
	clean_oldenv(list);
	setup_signals();
	if (ac != 1 || av[1] != NULL)
		return (84);
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
