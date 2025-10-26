/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:55:00 by ande-vat          #+#    #+#             */
/*   Updated: 2025/10/26 17:57:17 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

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
	ft_memset(ret, 0, s);
	return (ret);
}
