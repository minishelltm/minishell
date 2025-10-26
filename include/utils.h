/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio <tonio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:40:44 by tonio             #+#    #+#             */
/*   Updated: 2025/10/26 17:56:39 by tonio            ###   ########.fr       */
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
int		ft_strncmp(char *a, char *b, int size);
char	*ft_strdup(char const *src);
int		ft_strlen(char const *str);
char	*get_first_word(char *command);
char	*ft_pathcat(char *path, char *name);
char	**ft_str_to_word_array(char const *str);
char	*ft_strcat(char *s1, char *s2);
char	*split(char const *src, char sep, int index, int end);
int		includes(char *str, char c);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		is_ws(char c);
int		is_empty(char *str);
int		is_operator(char c);
int		is_quote(char c);
int		free_tab(char **tab);
void	*ft_memset(void *b, int c, size_t len);
int		ft_isalnum(int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, int start, int len);
void	*ft_calloc(int nmemb, int size);
#endif
