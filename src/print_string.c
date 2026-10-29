/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 12:03:14 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/29 08:30:07 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_null_string(t_options *opts)
{
	if (opts->precision < 0 || opts->precision >= 6)
		return (print_string("(null)", opts));
	if (opts->minwidth > 0)
		return (print_padding(0, opts->minwidth));
	return (0);
}

char	*get_printable_string(const char *str, t_options *opts)
{
	if (opts->precision >= 0 && (size_t) opts->precision < ft_strlen(str))
		return (ft_substr(str, 0, opts->precision));
	return (ft_strdup(str));
}

size_t	print_string(const char *str, t_options *opts)
{
	char	*s;
	int		len;

	if (str == NULL)
		return (print_null_string(opts));
	s = get_printable_string(str, opts);
	len = ft_strlen(s);
	if (len < opts->minwidth && !opts->rightpad)
		len += print_padding(0, opts->minwidth - len);
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}
