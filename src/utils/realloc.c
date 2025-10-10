/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:34:50 by tonio             #+#    #+#             */
/*   Updated: 2025/10/10 10:45:21 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size_to_copy;

	size_to_copy = old_size < new_size ? old_size : new_size; // FIX OMG
	if (old_size == 0)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	for (size_t i = 0; i < size_to_copy; ++i) // FIX OMG
		((char *)new_ptr)[i] = ((char *)ptr)[i];
	if (ptr)
		free(ptr);
	return (new_ptr);
}

void	free_tab(char **tab)
{
	for (int i = 0; tab[i] != NULL; i++) // FIX OMG
		free(tab[i]);
	free(tab);
}
