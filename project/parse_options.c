/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 09:49:30 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 11:51:02 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*int	parse_minwidth(char **str)
{
	return (-1);
}*/

int	parse_minwidth(char **str)
{
	if (ft_isdigit(**str) && **str != '0')
		return (parse_number(str));
	return (-1);
}

/*int	parse_precision(char **str, t_options *opts)
{
	return (-1);
}*/

int	parse_precision(char **str, t_options *opts)
{
	if (**str != '.')
		return (-1);
	(*str)++;
	opts->zero = 0;
	return (parse_number(str));
}

int	is_flag(char c)
{
	return (c == '#' || c == '-' || c == '0' || c == ' ' || c == '+');
}

void	parse_flags(char **str, t_options *opts)
{
	char	f;

	f = **str;
	while (is_flag(f))
	{
		if (f == '#')
			opts->hash = 1;
		if (f == ' ' && !opts->plus)
			opts->blank = 1;
		if (f == '0' && !opts->rightpad && opts->precision == -1)
			opts->zero = 1;
		if (f == '-')
		{
			opts->zero = 0;
			opts->rightpad = 1;
		}
		if (f == '+')
		{
			opts->blank = 0;
			opts->plus = 1;
		}
		(*str)++;
		f = **str;
	}
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
