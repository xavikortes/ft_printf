/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:45:27 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 19:31:18 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	new = ft_calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}
