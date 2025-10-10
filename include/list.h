/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:34:50 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:49:21 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stddef.h>
# include <stdlib.h>

typedef struct s_env_data
{
	char		*key;
	char		*value;
}				t_env_data;

typedef struct s_node
{
	t_env_data		data;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

t_node			*create_node(t_env_data data);
void			add_node(t_node *list, t_node *node);
void			free_list(t_node *list);
void			delete_node(t_node *list, t_node *node);
t_node			*find_node(t_node *list, char *key);
int				update_node(t_node *list, char *key, char *value);

#endif
