/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:52:36 by tonio             #+#    #+#             */
/*   Updated: 2025/10/25 13:23:43 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <stdlib.h>

void	make_quote_token(char *input, t_token **list, int *i)
{
	char	quote_char;
	t_token	*new_token;
	int		ct;

	new_token = init_token();
	quote_char = input[*i];
	new_token->quote_type = DQUOTE;
	ct = 0;
	(*i)++;
	if (quote_char == '\'')
		new_token->quote_type = SQUOTE;
	while (input[(*i) + ct] && input[(*i) + ct] != quote_char)
		ct++;
	if (input[(*i) + ct] == quote_char)
	{
		input[(*i) + ct] = '\0';
		new_token->value = ft_strdup(&input[*i]);
	}
	else // unmatched quote
		return (free_tokens(*list), free_tokens(new_token));
	input[(*i) + ct] = quote_char;
	*i += ct + 1;
	new_token->should_merge = !(is_ws(input[(*i)]) || is_operator(input[(*i)]));
	add_token_back(list, new_token);
}

void	make_word_token(char *input, t_token **list, int *i)
{
	t_token	*new_token;
	int		ct;

	new_token = init_token();
	ct = 0;
	while (!(is_ws(input[(*i) + ct]) || is_operator(input[(*i) + ct])
			|| is_quote(input[(*i) + ct]))
		&& input[(*i) + ct])
		ct++;
	if (ct == 0)
		return (free_tokens(new_token));
	new_token->should_merge = is_quote(input[(*i) + ct]);
	input[(*i) + ct] = '\0';
	new_token->value = ft_strdup(&input[(*i)]);
	(*i) += ct + 1;
	add_token_back(list, new_token);
}

void	make_op_token(char *input, t_token **list, int *i)
{
	t_token	*new_token;

	new_token = init_token();
	if (!new_token)
		return ;
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		new_token->type = HEREDOC;
		*i += 1;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		new_token->type = APPEND;
		*i += 1;
	}
	else if (input[*i] == '<')
		new_token->type = REDIR_IN;
	else if (input[*i] == '>')
		new_token->type = REDIR_OUT;
	else if (input[*i] == '|')
		new_token->type = PIPE;
	new_token->value = ft_strdup(""); // Value can be empty. I dont even really have to do that actually
	add_token_back(list, new_token);
	(*i)++;
}

t_token	*line_to_tokens(char *input)
{
	int		i;
	t_token	*list;

	i = 0;
	list = NULL;
	while (input[i])
	{
		if (is_ws(input[i]))
			i++;
		else if (is_operator(input[i]))
			make_op_token(input, &list, &i);
		else if (input[i] == '"' || input[i] == '\'')
			make_quote_token(input, &list, &i);
		else
			make_word_token(input, &list, &i);
	}
	return (list);
}
