/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ande-vat <ande-vat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:58:08 by ande-vat          #+#    #+#             */
/*   Updated: 2025/10/27 15:58:29 by ande-vat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envify.h"
#include "shell.h"
#include "utils.h"

int	myenv(t_node *env)
{
	char	**envarr;
	int		i;

	envarr = stringify(env);
	i = 0;
	while (envarr[i] != NULL)
	{
		write(1, envarr[i], ft_strlen(envarr[i]));
		write(1, "\n", 1);
		i++;
	}
	free_arr(envarr);
	return (0);
}
