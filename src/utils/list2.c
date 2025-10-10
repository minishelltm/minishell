/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:34:09 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:38:02 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "utils.h"

int	update_node(t_node *list, char *key, char *value)
{
	t_node	*node;

	node = find_node(list, key);
	if (node == NULL)
		return (-1);
	if (node->data.value != NULL)
		free(node->data.value);
	node->data.value = value;
	return (0);
}
