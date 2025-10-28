/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:31:23 by tonio             #+#    #+#             */
/*   Updated: 2025/10/28 18:09:36 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "list.h"

int	run_builtin(char **args, t_node *env);
int	ft_cd(char **args, t_node *env);
int	ft_pwd(char **args, t_node *env);
int	ft_echo(char **args, t_node *env);
int	ft_export(char **args, t_node *env);

#endif /* !BUILTINS_H */
