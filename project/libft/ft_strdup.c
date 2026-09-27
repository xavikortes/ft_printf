/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:42:09 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/24 17:42:10 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	void	*ptr;
	size_t	len;

	len = ft_strlen(str);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (ptr == NULL)
		return (ptr);
	ft_strlcpy(ptr, str, len + 1);
	return (ptr);
}
