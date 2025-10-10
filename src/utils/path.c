/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 02:04:53 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:45:18 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"

char	*ft_pathcat(char *path, char *name)
{
	char	*retval;

	retval = malloc(ft_strlen(path) + ft_strlen(name) + 2);
	retval = ft_strcat(path, "/");
	retval = ft_strcat(retval, name);
	return (retval);
}
