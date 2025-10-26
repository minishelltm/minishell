/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:31:48 by ande-vat          #+#    #+#             */
/*   Updated: 2025/10/26 17:50:12 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isdigit(int i)
{
	return (i >= '0' && i <= '9');
}

int	ft_isalpha(int i)
{
	return ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z'));
}


int	ft_isalnum(int i)
{
	return (ft_isalpha(i) || ft_isdigit(i));
}
