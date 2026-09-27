/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 12:26:08 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 17:19:11 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] == '\0')
			return (str2[i] * -1);
		if (str2[i] == '\0')
			return (str1[i]);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
