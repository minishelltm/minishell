/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmicael <mmicael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:40:44 by tonio             #+#    #+#             */
/*   Updated: 2025/10/22 20:23:28 by mmicael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>

typedef enum e_strtype
{
	ALPHANUM,
	NUM,
	ALPHA
}		t_strtype;
int		is_alphanum(char *str, t_strtype type);
int		ft_isalnum(int c);
int		ft_strncmp(char *a, char *b, int size);
int		skip_to_index(char const *str, char sep, int index);
char	*ft_strdup(char const *src);
int		ft_strlen(char const *str);
char	*ft_strdup_safe(char *s1, char *s2);
char	*get_first_word(char *command);
char	*ft_pathcat(char *path, char *name);
char	**ft_str_to_word_array(char const *str);
char	*ft_strcat(char *s1, char *s2);
char	*split(char const *src, char sep, int index, int end);
int		includes(char *str, char c);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		is_ws(char *str);
int		free_tab(char **tab);
char	*ft_strjoin(char const *s1, char const *s2);
void	setup_signals(void);
int		countdigits(int nb);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);

#endif
