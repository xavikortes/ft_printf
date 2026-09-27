/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 10:53:13 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 11:01:32 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (str == NULL || f == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		(*f)(i, str + i);
		i++;
	}
}
