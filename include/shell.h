/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:39:54 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 08:18:46 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "list.h"
# include "parser.h"
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_exit_code;
int			shell(t_node *env);
char		*find_bin_path(char *path, char *name);
char		**parse_semicolon(char *line);
char		*find_bin(char **args, t_node *env);
t_token		*line_to_tokens(char *input);
t_command	*token_to_cmd(t_token *tokens);
t_command	*parse_input(char *line, t_node *env);
char		*ft_itoa(int i);
#endif
