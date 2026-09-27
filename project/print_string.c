/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 12:03:14 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:03:35 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_string(const char *str, t_options *opts)
{
	char	*s;
	int		len;
	int		str_len;

	if (str == NULL)
		return (print_string("(null)", opts));
	s = (char *) str;
	str_len = ft_strlen(s);
	if (opts->precision != -1)
		s = ft_substr(str, 0, opts->precision);
	else
		s = ft_substr(str, 0, str_len);
	len = ft_strlen(s);
	if (len < opts->minwidth && !opts->rightpad)
		len += print_padding(0, opts->minwidth - len);
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}
