/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 12:20:55 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:20:59 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_ptr(void *ptr, t_options *opts)
{
	if (ptr == NULL)
		return (print_string("(nil)", opts));
	opts->hash = 1;
	return (print_hex((uintptr_t) ptr, 0, opts));
}
