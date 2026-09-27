/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:54:54 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:13:27 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_printer_len(int n, t_options *opts)
{
	char	*s;
	int		len;

	s = ft_itoa(n);
	len = ft_strlen(s);
	if (n < 0)
		len--;
	if (opts->precision > len)
		len = opts->precision;
	if (n < 0)
		len++;
	else if (opts->plus || opts->blank)
		len++;
	free(s);
	return (len);
}

size_t	print_int_prefixes(long n, t_options *opts)
{
	size_t	len;

	len = 0;
	if (n < 0)
		len += write_char('-');
	else if (opts->plus)
		len += write_char('+');
	else if (opts->blank)
		len += write_char(' ');
	return (len);
}

size_t	print_int(long n, t_options *opts)
{
	char	*s;
	int		len;
	int		str_len;

	if (n == 0 && opts->precision == 0)
		return (0);
	len = 0;
	str_len = int_printer_len(n, opts);
	if (!opts->zero && !opts->rightpad && opts->minwidth > str_len)
		len += print_padding(0, opts->minwidth - str_len);
	len += print_int_prefixes(n, opts);
	if (opts->zero && opts->minwidth > str_len)
		len += print_padding(1, opts->minwidth - str_len);
	if (n >= 0)
		s = ft_utoa_base(n, "0123456789");
	else
		s = ft_utoa_base(-n, "0123456789");
	str_len = ft_strlen(s);
	if (opts->precision > str_len)
		len += print_padding(1, opts->precision - str_len);
	len += str_len;
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}
