/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:44:13 by tonio             #+#    #+#             */
/*   Updated: 2025/10/25 18:13:44 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strncmp(char *a, char *b, int size)
{
	int	i;

	i = 0;
	while (a[i] == b[i] && a[i] != '\0' && b[i] != '\0' && (i < size - 1
			|| size == 0))
	{
		i++;
	}
	return (a[i] - b[i]);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!is_ws(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	includes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_alphanum(char *str, t_strtype type)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (type == ALPHANUM && !((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0'
					&& str[i] <= '9') || str[i] == '_'))
			return (0);
		if (type == NUM && !(str[i] >= '0' && str[i] <= '9'))
			return (0);
		if (type == ALPHA && !((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')))
			return (0);
		i++;
	}
	return (1);
}
