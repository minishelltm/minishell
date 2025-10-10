/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:34:00 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:45:12 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>

t_node	*create_node(t_env_data data)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_node(t_node *list, t_node *node)
{
	if (list == NULL)
		return ;
	if (list->next == NULL)
	{
		list->next = node;
		node->prev = list;
		return ;
	}
	add_node(list->next, node);
}

void	free_list(t_node *list)
{
	if (list == NULL)
		return ;
	free_list(list->next);
	free(list->data.key);
	free(list->data.value);
	free(list);
}

void	delete_node(t_node *list, t_node *node)
{
	if (list == NULL)
		return ;
	if (list->next == node)
	{
		list->next = list->next->next;
		free(node->data.key);
		free(node->data.value);
		free(node);
		return ;
	}
	delete_node(list->next, node);
}

t_node	*find_node(t_node *list, char *key)
{
	if (list == NULL)
	{
		return (NULL);
	}
	if (ft_strncmp(list->data.key, key, 0) == 0)
		return (list);
	return (find_node(list->next, key));
}
