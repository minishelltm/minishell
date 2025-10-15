/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:43:08 by tonio             #+#    #+#             */
/*   Updated: 2025/10/15 18:37:57 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
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

char	*ft_strdup(char const *src)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(src) + 1);
	i = 0;
	if (src == NULL || dest == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	if (dest[0] == '\0')
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == NULL)
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (dest == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

// FIX OMG
char	*split(char const *str, char sep, int index, int end)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*ret;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(str);
	ret = malloc(len + 1);
	while (j < index)
	{
		if (str[i] == sep)
		{
			j++;
		}
		i++;
	}
	j = 0;
	while (str[i] != '\0' && (k < end || end == 0))
	{
		ret[j] = str[i];
		if (str[i] == sep)
			k++;
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
