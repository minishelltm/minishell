/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:58:08 by ande-vat          #+#    #+#             */
/*   Updated: 2025/10/28 18:40:27 by tonio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envify.h"
#include "shell.h"
#include "utils.h"

static int	check_env_key(char *key)
{
	if (!((key[0] >= 'a' && key[0] <= 'z') || (key[0] >= 'A' && key[0] <= 'Z')
			|| key[0] == '_'))
	{
		write(2, "export: Variable name must begin with a letter or _.\n", 54);
		return (1);
	}
	if (!is_alphanum(key, ALPHANUM))
	{
		write(2,
			"export: Variable name must contain alphanumeric characters.\n",
			61);
		return (1);
	}
	return (0);
}

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

int	handle_export(char *arg, t_node *env)
{
	char	*key;
	char	*value;
	char	*key_with_eq;

	key = ft_strdup(arg);
	value = ft_strdup("");
	if (includes(key, '='))
	{
		free(key);
		free(value);
		key = split(arg, '=', 0, 1);
		value = split(arg, '=', 1, 0);
		key[ft_strlen(key) - 1] = '\0';
	}
	if (check_env_key(key) == 1)
		return (free(key), free(value), 1);
	key_with_eq = ft_strjoin(key, "=");
	free(key);
	update_env(key_with_eq, value, env);
	return (0);
}

int	ft_export(char **args, t_node *env)
{
	int	i;
	int	r;

	if (!args[1])
		return (myenv(env));
	i = 1;
	r = 0;
	while (args[i])
	{
		r = handle_export(args[i], env);
		if (r == 1)
			return (1);
		i++;
	}
	return (0);
}
