/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:44:13 by tonio             #+#    #+#             */
/*   Updated: 2025/10/29 17:11:06 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_ws(char c)
{
	return (c == ' ' || (c <= 13 && c >= 9));
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	is_dot(char *name)
{
	if (ft_strncmp(name, ".", 0) == 0)
		return (1);
	if (ft_strncmp(name, "..", 0) == 0)
		return (1);
	return (0);
}

char	*split_path(const char *s, int idx)
{
	char	*tmp;
	int		n;

	tmp = split(s, ':', idx, 1);
	if (!tmp)
		return (NULL);
	n = ft_strlen(tmp);
	if (n && tmp[n - 1] == ':')
		tmp[--n] = '\0';
	if (!(*tmp))
	{
		return (free(tmp), NULL);
	}
	return (tmp);
}
