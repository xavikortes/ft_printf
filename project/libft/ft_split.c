/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:23:10 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/29 10:00:36 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calculate_len(char *s, char c)
{
	char	*ptr;

	if (c == '\0')
		return (1);
	if (*s == '\0')
		return (0);
	ptr = ft_strchr(s, c);
	if (ptr == NULL)
		return (1);
	if (ptr == s)
		return (calculate_len(++ptr, c));
	return (1 + calculate_len(++ptr, c));
}

static char	**free_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static char	**set_items(char **arr, int i, char *s, char c)
{
	int		size;
	char	*ptr;

	if (*s == '\0')
		return (arr);
	ptr = ft_strchr(s, c);
	if (c == '\0' || ptr == NULL)
		size = ft_strlen(s);
	else
		size = ptr - s;
	if (size == 0)
		return (set_items(arr, i, ++ptr, c));
	arr[i] = ft_calloc(size + 1, sizeof(char));
	if (arr[i] == NULL)
		return (free_arr(arr, i));
	ft_strlcpy(arr[i], s, size + 1);
	if (c == '\0' || ptr == NULL)
		return (arr);
	return (set_items(arr, i + 1, ++ptr, c));
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**arr;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	ptr = (char *) s;
	len = calculate_len(ptr, c);
	arr = ft_calloc(len + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = set_items(arr, 0, ptr, c);
	if (arr == NULL)
		return (NULL);
	arr[len] = NULL;
	return (arr);
}
