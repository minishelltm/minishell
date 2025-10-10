/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envify.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:34:21 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:41:53 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIFY_H
# define ENVIFY_H
# include "list.h"

t_node	*envify(char **env);
char	**stringify(t_node *list);
t_node	*update_env(char *key, char *value, t_node *list);
#endif /* !ENVIFY_H_ */
