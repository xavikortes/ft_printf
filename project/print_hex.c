/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 12:17:31 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:36:19 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_hex_prefix(int uppercase)
{
	ft_putchar_fd('0', 1);
	if (uppercase)
		ft_putchar_fd('X', 1);
	else
		ft_putchar_fd('x', 1);
	return (2);
}

int	calculate_print_hex_len(uintptr_t n, char *s, t_options *opts)
{
	int	len;

	len = ft_strlen(s);
	if (opts->precision > len)
		len = opts->precision;
	if (opts->hash && n > 0)
		len += 2;
	return (len);
}

size_t	print_hex(uintptr_t n, int uppercased, t_options *opts)
{
	char	*s;
	int		len;
	int		str_len;

	if (n == 0 && opts->precision == 0)
		return (0);
	len = 0;
	if (uppercased)
		s = ft_utoa_base(n, "0123456789ABCDEF");
	else
		s = ft_utoa_base(n, "0123456789abcdef");
	str_len = calculate_print_hex_len(n, s, opts);
	if (!opts->zero && !opts->rightpad && opts->minwidth > str_len)
		len += print_padding(0, opts->minwidth - str_len);
	if (opts->hash && n != 0)
		len += print_hex_prefix(uppercased);
	if (opts->zero && !opts->rightpad && opts->minwidth > str_len)
		len += print_padding(1, opts->minwidth - str_len);
	str_len = ft_strlen(s);
	if (opts->precision > str_len)
		len += print_padding(1, opts->precision - str_len);
	len += str_len;
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}
