/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:38:43 by tonio             #+#    #+#             */
/*   Updated: 2025/10/15 18:33:20 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "shell.h"
#include "utils.h"
#include <stdlib.h>

t_env_data	dataify(char *entry)
{
	t_env_data	data;
	char		*key;
	char		*value;

	key = split(entry, '=', 0, 1);
	value = split(entry, '=', 1, 0);
	data.key = key;
	data.value = value;
	return (data);
}

t_node	*envify(char **env)
{
	t_env_data	data;
	t_node		*list;
	int			i;

	i = 1;
	data = dataify(env[0]);
	list = create_node(data);
	while (env[i] != NULL)
	{
		data = dataify(env[i]);
		add_node(list, create_node(data));
		i++;
	}
	return (list);
}

char	**stringify(t_node *list)
{
	t_node		*listcpy;
	int			i;
	char		**envstrarr;
	t_env_data	data;

	listcpy = list;
	i = 0;
	while (listcpy != NULL)
	{
		i++;
		listcpy = listcpy->next;
	}
	envstrarr = malloc((i + 1) * sizeof(char *));
	listcpy = list;
	i = 0;
	while (listcpy != NULL)
	{
		data = listcpy->data;
		envstrarr[i] = ft_strcat(data.key, data.value);
		listcpy = listcpy->next;
		i++;
	}
	envstrarr[i] = NULL;
	return (envstrarr);
}

t_node	*update_env(char *key, char *value, t_node *list)
{
	t_env_data	data;
	t_node		*node;

	data = (t_env_data){key, value};
	node = create_node(data);
	if (update_node(list, key, value) == 0)
		return (list);
	add_node(list, node);
	return (list);
}
