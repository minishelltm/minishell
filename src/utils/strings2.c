/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:44:13 by tonio             #+#    #+#             */
/*   Updated: 2025/10/11 19:50:50 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	includes(char *str, char c)
{
	for (int i = 0; str[i] != '\0'; i++) // FIX OMG
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

int	is_ws(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) // FIX OMG
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
	}
	return (0);
}

int	is_alphanum(char *str, t_strtype type)
{
	for (int i = 0; str[i] != '\0'; i++) // FIX OMG
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
	}
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (new == NULL)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
