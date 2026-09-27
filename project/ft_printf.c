/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 09:50:28 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:29:36 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *format, ...)
{
	int		len;
	va_list	args;

	len = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			len += print_argument(args, (char **) &format);
		}
		else
			len += write_char(*format);
		format++;
	}
	va_end(args);
	return (len);
}
