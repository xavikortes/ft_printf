/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 12:15:21 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:17:03 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	uint_printer_len(uintptr_t n, t_options *opts)
{
	char	*s;
	int		len;

	s = ft_utoa_base(n, "0123456789");
	len = ft_strlen(s);
	if (opts->precision > len)
		len = opts->precision;
	if (opts->plus || opts->blank)
		len++;
	free(s);
	return (len);
}

size_t	print_uint(uintptr_t n, t_options *opts)
{
	char	*s;
	int		len;
	int		str_len;

	if (n == 0 && opts->precision == 0)
		return (0);
	len = uint_printer_len(n, opts);
	if (!opts->rightpad && opts->minwidth > len)
		len = print_padding(opts->zero, opts->minwidth - len);
	else
		len = 0;
	if (opts->plus)
		len += write_char('+');
	else if (opts->blank)
		len += write_char(' ');
	s = ft_utoa_base(n, "0123456789");
	str_len = ft_strlen(s);
	if (opts->precision > str_len)
		len += print_padding(1, opts->precision - str_len);
	len += str_len;
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}
