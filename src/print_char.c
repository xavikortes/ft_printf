/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 12:01:37 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/29 08:06:23 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_char(unsigned char c, t_options *opts)
{
	int	len;

	len = 1;
	if (opts->minwidth > 0 && !opts->rightpad)
		len += print_padding(0, opts->minwidth - len);
	ft_putchar_fd(c, 1);
	return (len);
}
