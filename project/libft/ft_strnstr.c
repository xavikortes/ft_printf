/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 12:37:25 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 19:34:37 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(to_find);
	if (len == 0)
		return ((char *) str);
	if (size < len)
		return (NULL);
	while (str[i] != '\0' && i < size - len)
	{
		if (str[i] == *to_find)
		{
			if (!ft_strncmp(str + i, to_find, len))
				return ((char *) str + i);
		}
		i++;
	}
	return (NULL);
}
