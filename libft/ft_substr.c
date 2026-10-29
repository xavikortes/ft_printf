/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:45:27 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/29 09:36:42 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	str_len;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_calloc(1, sizeof(char)));
	str_len -= start;
	if (len == SIZE_MAX)
		len--;
	if (len > str_len)
		new = ft_calloc(str_len + 1, sizeof(char));
	else
		new = ft_calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}
