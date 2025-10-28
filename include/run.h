/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:38:57 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 16:44:01 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H
# include "list.h"
# include "parser.h"
# include <sys/types.h>

typedef struct s_single_res
{
	int		hd_fd;
	int		is_builtin;
	int		status;
}	t_single_res;

typedef struct s_pipeline
{
	t_node	*env;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	*pids;
	int		pcount;
	int		count;
	int		*heredocs;
}	t_pipeline;

void	restore_stdio(int saved_in, int saved_out);
int		is_b_in(char *name);
int		run_bin(char *cmd, char **args, char **env);
int		run_builtin(char **args, t_node *env);
int		run_commands(t_command *commands, t_node *env);
int		collect_heredoc(const char *delim);
void	cmd_not_found(char *name);
int		apply_redirections(t_command *cmd, int heredoc_fd);
void	parent_after_fork(t_pipeline *pl, int has_next);
void	child_exec_command(t_command *cmd, t_pipeline *pl,
			int heredoc_fd, int has_next);
int		*prepare_heredocs(t_command *cmds, int count);
int		count_commands(t_command *cmd);
int		pipeline_init(t_pipeline *pl, t_node *env, t_command *cmds);
int		open_pipe_if_needed(t_pipeline *pl, int has_next);
void	restore_stdin(int saved);
int		handle_status(int status);
int		handle_child(char *path_to_bin, char **args, char **env);
int		handle_single(t_command *commands, t_node *env);
int		run_pipeline(t_command *commands, t_node *env);
int		apply_out_redir(t_command *cmd);
int		apply_heredoc_redir(int heredoc_fd);
int		apply_in_redir(t_command *cmd);
void	reset_signals(void);
#endif
