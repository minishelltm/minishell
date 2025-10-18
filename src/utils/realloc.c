/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:34:50 by tonio             #+#    #+#             */
/*   Updated: 2025/10/14 03:52:04 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	i;

	i = 0;
	if (old_size == 0)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	while (i < old_size && i < new_size)
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		++i;
	}
	while (i < new_size)
	{
		((char *)new_ptr)[i] = '\0';
		++i;
	}
	return (free(ptr), new_ptr);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
	}
	free(tab);
}
