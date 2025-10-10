/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_word_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:35:32 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:45:24 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"
#include <stddef.h>

char	is_nonws(char c)
{
	char	retval;

	retval = 0;
	if (c >= 33 && c <= 126)
	{
		retval = 1;
	}
	return (retval);
}

int	findword(char const *str, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (index == 0 && is_nonws(str[0]) == 1)
		return (0);
	if (is_nonws(str[0]) == 0)
		i = -1;
	for (; str[j] != '\0'; j++)
	{
		if (is_nonws(str[j]) == 1 && is_nonws(str[j - 1]) == 0)
			i++;
		if (i == index)
			break ;
	}
	if (i != index)
	{
		return (-1);
	}
	return (j);
}

char	*getword(char const *str, int index)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = findword(str, index);
	ret = NULL;
	if (j == -1)
		return (NULL);
	for (; str[j + i] != '\0' && is_nonws(str[j + i]) == 1; i++) // FIX OMG
		continue ;
	ret = malloc(i + 1);
	i = 0;
	for (; str[j] != '\0' && is_nonws(str[j]) == 1; j++) // FIX OMG
	{
		ret[i] = str[j];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_str_to_word_array(char const *str)
{
	char	**ret;
	int		i;
	char	*tmp;

	i = 0;
	tmp = getword(str, i);
	for (; tmp != NULL; i++)
	{
		free(tmp);
		tmp = getword(str, i);
	}
	ret = malloc(i * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	tmp = getword(str, i);
	for (; tmp != NULL; tmp = getword(str, i))
	{
		ret[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
