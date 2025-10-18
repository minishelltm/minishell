/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:43:08 by tonio             #+#    #+#             */
/*   Updated: 2025/10/14 13:56:49 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"

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
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
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

static int	find_start(const char *str, char sep, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && count < index)
	{
		if (str[i] == sep)
			count++;
		i++;
	}
	return (i);
}

char	*split(char const *str, char sep, int index, int end)
{
	int		i;
	int		k;
	int		j;
	int		len;
	char	*ret;

	k = 0;
	j = 0;
	len = ft_strlen(str);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	i = find_start(str, sep, index);
	while (str[i] && (k < end || end == 0))
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
