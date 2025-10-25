/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:36:39 by tonio             #+#    #+#             */
/*   Updated: 2025/10/25 18:23:38 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envify.h"
#include "list.h"
#include "shell.h"
#include "utils.h"
#include <signal.h>
#include "parser.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		write(2, "\n$>", 3);
	return ;
}

void	clean_oldpwd(t_node *list)
{
	update_env("OLDPWD=", ft_strdup(""), list);
}

// int	main(int ac, char **av, char **env)
// {
// 	int		retval;
// 	t_node	*list;

// 	retval = 0;
// 	list = envify(env);
// 	clean_oldpwd(list);
// 	signal(SIGINT, sig_handler);
// 	if (ac != 1 || av[1] != NULL) // handle -c ?
// 	{
// 		return (84);
// 	}
// 	retval = shell(list);
// 	free_list(list);
// 	return (retval);
// }

void print_tokens(t_token *list)
{
	t_token *t = list;
	while (t)
	{
		printf("token: val= *%s*\n\ttype=%d\n\tquote_type=%d\n\tshould_merge=%d\n\tnext=%p \n\tprev=%p\n\n", t->value, t->type, t->quote_type, t->should_merge, t->next, t->prev);
		t = t->next;
	}
	printf("\n\n");
}

void print_cmds(t_command *list)
{
	t_command *c = list;
	int i = 0;
	while (c)
	{
		printf ("command: args =");
		while (c->args && c->args[i])
			printf("\n\t\t*%s*", c->args[i++]);
		printf("\ninfile=*%s*\noutfile=*%s*\nappend=%d\nheredoc=%s\nnext=%p\nprev=%p\n\n", c->infile, c->outfile, c->append, c->heredoc, c->next, c->prev);
		c = c->next;
	}
}

// test parsing
int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char		*line;
	t_token		*args;
	int			interrupt;
	t_command	*cmds;
	args = NULL;
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
		args = line_to_tokens(line);
		print_tokens(args);
		cmds = token_to_cmd(args);
		print_cmds(cmds);
		free(line);
	}
	return (0);
}