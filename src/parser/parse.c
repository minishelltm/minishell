/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:38:36 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 06:33:55 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
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

void	expand_dollar(t_token *tks, t_node *env)
{
	char	*before_dollar;
	int		i;
	char	*new_value;
	int		j;

	i = 0;
	j = 0;
	while (tks->value[i] != '$')
		i++;
	before_dollar = ft_substr(tks->value, 0, i);
	i++;
	while (tks->value[i + j] && (ft_isalnum(tks->value[i + j])
			|| tks->value[i + j] != '_'))
		j++;
	new_value = ft_strjoin(before_dollar, expand_var(&tks->value[i - 1], env));
	new_value = ft_strjoin(new_value, &tks->value[i + j]);
	printf("new = %s\n", new_value);
	free(tks->value);
	tks->value = new_value;
	return ;
}

void	merge(t_token *c, t_token *n)
{
	char	*new;

	if (c && n)
	{
		new = ft_strjoin(c->value, n->value);
		free(c->value);
		c->value = new;
		c->next = n->next;
	}
}

void	merge_and_expand(t_token *tks, t_node *env)
{
	t_token	*t;

	t = tks;
	while (t)
	{
		if (t->quote_type != SQUOTE && includes(t->value, '$'))
			expand_dollar(t, env);
		t = t->next;
	}
	t = tks;
	while (t)
	{
		if (t->should_merge)
			merge(t, t->next);
		t = t->next;
	}
}

t_command	*parse_input(char *line, t_node *env)
{
	t_token		*tks;
	t_command	*cmds;

	tks = line_to_tokens(line);
	merge_and_expand(tks, env);
	if (tks == NULL)
		return (NULL);
	cmds = token_to_cmd(tks);
	return (cmds);
}
