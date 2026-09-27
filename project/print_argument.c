/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 12:22:31 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:38:37 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_conversion(char conv, va_list args, t_options *opts)
{
	if (conv == '%')
		return (print_char('%', opts));
	if (conv == 'c')
		return (print_char(va_arg(args, int), opts));
	if (conv == 's')
		return (print_string(va_arg(args, const char *), opts));
	if (conv == 'i')
		return (print_int(va_arg(args, int), opts));
	if (conv == 'd')
		return (print_int(va_arg(args, int), opts));
	if (conv == 'u')
		return (print_uint(va_arg(args, unsigned int), opts));
	if (conv == 'p')
		return (print_ptr(va_arg(args, void *), opts));
	if (conv == 'x')
		return (print_hex(va_arg(args, unsigned int), 0, opts));
	if (conv == 'X')
		return (print_hex(va_arg(args, unsigned int), 1, opts));
	return (0);
}

size_t	print_argument(va_list args, char **fmt)
{
	int			len;
	t_options	*opts;
	char		conv;

	opts = parse_options(fmt);
	conv = **fmt;
	len = print_conversion(conv, args, opts);
	if (opts->rightpad && opts->minwidth > len)
		len += print_padding(0, opts->minwidth - len);
	free(opts);
	return (len);
}
