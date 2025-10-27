/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 02:04:53 by tonio             #+#    #+#             */
/*   Updated: 2025/10/27 11:00:06 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "utils.h"

char	*ft_pathcat(char *path, char *name)
{
	char	*w_slash;
	char	*retval;

	w_slash = ft_strcat(path, "/");
	retval = ft_strcat(w_slash, name);
	free(w_slash);
	return (retval);
}
