/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 11:51:09 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/27 12:14:39 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_number(char **str)
{
	int	n;

	n = 0;
	while (ft_isdigit(**str))
	{
		n = n * 10 + (**str - '0');
		(*str)++;
	}
	return (n);
}

int	calculate_utoa_base_len(uintptr_t n, size_t baselen)
{
	if (n / baselen == 0)
		return (1);
	return (1 + calculate_utoa_base_len(n / baselen, baselen));
}

void	set_utoa_base_char(char *str, int i, uintptr_t n, char *base)
{
	size_t	baselen;

	baselen = ft_strlen(base);
	str[i] = base[n % baselen];
	if (n / baselen == 0)
		return ;
	set_utoa_base_char(str, i - 1, n / baselen, base);
}

char	*ft_utoa_base(uintptr_t n, char *base)
{
	int		len;
	size_t	baselen;
	char	*str;

	baselen = ft_strlen(base);
	len = calculate_utoa_base_len(n, baselen);
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	set_utoa_base_char(str, len - 1, n, base);
	return (str);
}
