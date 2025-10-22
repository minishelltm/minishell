/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:44:13 by tonio             #+#    #+#             */
/*   Updated: 2025/10/22 20:22:51 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_ws(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
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

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	int		sign;
	char	*new;

	nb = n;
	i = countdigits(nb);
	sign = 0;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	new[i] = '\0';
	if (nb < 0)
	{
		new[0] = '-';
		nb *= -1;
		sign++;
	}
	while (i > sign)
	{
		i--;
		new[i] = (nb % 10) + '0';
		nb /= 10;
	}
	return (new);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < siz)
	{
		dst[i] = src[i];
		i++;
	}
	if (siz > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
