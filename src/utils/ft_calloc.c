/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:55:00 by ande-vat          #+#    #+#             */
/*   Updated: 2025/11/01 05:34:22 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(int nmemb, int size)
{
	int		s;
	void	*ret;

	s = nmemb * size;
	if (nmemb <= 0 || size <= 0)
		return (malloc(0));
	if (s / size != nmemb || s <= 0)
		return (NULL);
	ret = malloc(s);
	if (!ret)
		return (NULL);
	ft_bzero(ret, s);
	return (ret);
}
