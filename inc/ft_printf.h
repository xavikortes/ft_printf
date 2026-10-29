/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 09:30:39 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/29 08:45:41 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_options
{
	int	hash;
	int	rightpad;
	int	zero;
	int	plus;
	int	blank;
	int	minwidth;
	int	precision;
}	t_options;

int			ft_printf(char const *format, ...);

char		*ft_utoa_base(uintptr_t n, char *base);
int			write_char(unsigned char c);
int			parse_number(char **str);
t_options	*parse_options(char **str);

size_t		print_padding(int iszero, size_t len);
size_t		print_char(unsigned char c, t_options *opts);
size_t		print_string(const char *str, t_options *opts);
size_t		print_int(long n, t_options *opts);
size_t		print_uint(uintptr_t n, t_options *opts);
size_t		print_hex(uintptr_t n, int uppercased, t_options *opts);
size_t		print_ptr(void *ptr, t_options *opts);
size_t		print_argument(va_list args, char **fmt);

#endif
