/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 03:38:36 by tonio             #+#    #+#             */
/*   Updated: 2025/10/18 03:33:29 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "shell.h"
#include "utils.h"

int	is_not_null(void *ptr)
{
	if (ptr == NULL)
		return (0);
	return (1);
}

static char	**split_tab(char *line, char *sep)
{
	int		i;
	char	*ptr;
	char	**ret;
	int		j;

	j = 0;
	i = 0;
	ptr = line;
	ret = NULL;
	while (line[j] != '\0')
	{
		if (ft_strncmp(&line[j], sep, ft_strlen(sep)) == 0)
		{
			line[j] = '\0';
			ret = ft_realloc(ret, sizeof(char *) * i, sizeof(char *) * (i + 1));
			ret[i] = ft_strdup(ptr);
			i += is_not_null(ret[i]);
			ptr = &line[j + 1];
		}
		j++;
	}
	ret = ft_realloc(ret, sizeof(char *) * i, sizeof(char *) * (i + 2));
	ret[i] = ft_strdup(ptr);
	ret[i + 1] = NULL;
	return (free(line), ret);
}

char	**parse_semicolon(char *line)
{
	char	**ret;

	ret = NULL;
	ret = split_tab(line, ";");
	return (ret);
}
