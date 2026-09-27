/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 13:12:54 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 10:41:18 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (dst <= src || src + n < dst)
		return (ft_memcpy(dst, src, n));
	while (n > 0)
	{
		ft_memset(dst + n - 1, ((char *) src)[n - 1], 1);
		n--;
	}
	return (dst);
}
