/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:43:33 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 19:25:58 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	l1;
	size_t	l2;

	if (s1 == NULL)
		return ((char *) s2);
	if (s2 == NULL)
		return ((char *) s1);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = ft_calloc(l1 + l2 + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s1, l1 + 1);
	ft_strlcat(new, s2, l1 + l2 + 1);
	return (new);
}
