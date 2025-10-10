/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:38:57 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:41:28 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H
# include "list.h"

int	run_bin(char *cmd, char **args, char **env);
int	run_builtin(char **args, t_node *env);

#endif
