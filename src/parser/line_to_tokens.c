/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:16:08 by ande-vat          #+#    #+#             */
/*   Updated: 2025/10/23 14:51:41 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "utils.h"
#include <stdbool.h>

// TODO implement
void	add_last(t_token *lst, t_token_type type, char *val, bool no_expand)
{
	return ;
}

bool	is_op(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

void	handle_word(t_token *tokens, int *i, char *line)
{
	char	*val;
	int		j;
	char	buffer;

	j = 0;
	while (!is_ws(line[(*i) + j]) && !is_op(line[(*i) + j]))
		j++;
	buffer = line[(*i) + j];
	line[(*i) + j] = '\0';
	val = ft_strdup(&line[*i]);
	line[(*i) + j] = buffer;
	(*i) += j;
}

void	handle_quotes(t_token *tokens, int *i, char *line)
{
	char	quote;
	char	*val;

	quote = line[*i];
	(*i)++;
	val = split(&line[*i], quote, 0, 1);
	(*i) += ft_strlen(val);
	if (quote == '\'')
		add_last(tokens, WORD, val, true);
	else
		add_last(tokens, WORD, val, false);
}

t_token	*line_to_tokens(char *line)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		while (is_ws(line[i]))
			i++;
		if (line[i] == '"' || line[i] == '\'')
			handle_quotes(tokens, &i, line);
		else if (is_op(line[i]))
			handle_op(tokens, &i, line);
		else
			handle_word(tokens, &i, line);
		i++;
	}
	return (tokens);
}
