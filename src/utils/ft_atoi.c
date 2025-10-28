/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:52:12 by ande-vat          #+#    #+#             */
/*   Updated: 2025/10/28 12:47:34 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	isws(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi(char const *src)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (isws(*src))
		src++;
	if (*src == '-')
	{
		sign *= -1;
		src++;
	}
	else if (*src == '+')
		src++;
	while (*src >= '0' && *src <= '9')
	{
		res = res * 10 + *src - '0';
		src++;
	}
	return (res * sign);
}
