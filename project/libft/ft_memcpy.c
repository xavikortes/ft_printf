/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 13:12:54 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 16:54:53 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL || src == NULL)
		return (dst);
	i = 0;
	while (i < n)
	{
		ft_memset(dst + i, ((char *) src)[i], 1);
		i++;
	}
	return (dst);
}
