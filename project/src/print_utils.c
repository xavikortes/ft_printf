/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:59:34 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:05:21 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_char(unsigned char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

size_t	print_padding(int is_zero, size_t len)
{
	size_t	n;

	n = len;
	while (n > 0)
	{
		if (is_zero)
			write_char('0');
		else
			write_char(' ');
		n--;
	}
	return (len);
}
