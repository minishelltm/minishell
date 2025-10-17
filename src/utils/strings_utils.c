/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:51:01 by mmicael           #+#    #+#             */
/*   Updated: 2025/10/17 19:50:47 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"

char	*ft_strdup_safe(char *s1, char *s2)
{
	if (s1 == NULL)
		return (ft_strdup(s2));
	else
		return (ft_strdup(s1));
}

int	skip_to_index(char const *str, char sep, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && j < index)
	{
		if (str[i] == sep)
			j++;
		i++;
	}
	return (i);
}
