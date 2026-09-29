/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 09:49:30 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/28 08:38:10 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_minwidth(char **str)
{
	(void) str;
	return (-1);
}

int	parse_precision(char **str, t_options *opts)
{
	(void) str;
	(void) opts;
	return (-1);
}

void	parse_flags(char **str, t_options *opts)
{
	(void) str;
	(void) opts;
}

t_options	*parse_options(char **str)
{
	t_options	*opts;

	opts = ft_calloc(1, sizeof(t_options));
	opts->hash = 0;
	opts->rightpad = 0;
	opts->zero = 0;
	opts->plus = 0;
	opts->blank = 0;
	opts->minwidth = -1;
	opts->precision = -1;
	parse_flags(str, opts);
	opts->minwidth = parse_minwidth(str);
	opts->precision = parse_precision(str, opts);
	return (opts);
}
