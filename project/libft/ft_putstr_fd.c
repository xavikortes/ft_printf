/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:44:56 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 10:08:05 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != 0)
		ft_putchar_fd(s[i++], fd);
}
