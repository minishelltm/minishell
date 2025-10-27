/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:33:51 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 08:15:58 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	countdigits(int nb)
{
	int		count;
	long	i;

	count = 1;
	i = nb;
	if (nb < 0)
	{
		i *= -1;
		count++;
	}
	while (i > 9)
	{
		i /= 10;
		count++;
	}
	return (count);
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
