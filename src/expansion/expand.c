/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:53:40 by mmicael           #+#    #+#             */
/*   Updated: 2025/10/22 20:29:23 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"

char	*expand_var(char *arg, t_node *env)
{
	char	*name;
	int		len;
	char	*var;
    char	*with_equal;
	t_node	*node;

	if (ft_strncmp(arg, "$?", 2) == 0)
		return (ft_itoa(g_exit_code));
	name = arg + 1;
	while (*name && (ft_isalnum(*name) || *name == '_'))
		name++;
	len = name - (arg + 1);
	var = malloc(len + 1);
    if (!var)
		return (NULL);
	ft_strlcpy(var, arg + 1, len + 1);
    with_equal = ft_strjoin(var, "=");
	node = find_node(env, with_equal);
	free(var);
    free(with_equal);
	if (!node)
		return (ft_strdup(""));
	return (ft_strdup(node->data.value));
}

void	expand_dollars(char **args, t_node *env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1] != '\0')
		{
			expanded = expand_var(args[i], env);
			free(args[i]);
			args[i] = expanded;
		}
		i++;
	}
}
