/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 09:50:28 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/29 08:08:51 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *format, ...)
{
	int		len;
	va_list	args;

	if (format == NULL)
		return (0);
	len = ft_strlen(format);
	if (len == 1 && *format == '%')
		return (0);
	len = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%' && *(format + 1) != '\0')
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
