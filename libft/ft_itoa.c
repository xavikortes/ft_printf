/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:11:27 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 16:41:11 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calculate_len(long n)
{
	if (n < 0)
		return (1 + calculate_len(-n));
	if (n / 10 == 0)
		return (1);
	return (1 + calculate_len(n / 10));
}

static void	set_char(char *str, int i, long n)
{
	if (n < 0)
	{
		str[0] = '-';
		return (set_char(str, i, -n));
	}
	str[i] = (n % 10) + '0';
	if (n / 10 == 0)
		return ;
	set_char(str, i - 1, n / 10);
}

char	*ft_itoa(int num)
{
	int		len;
	long	n;
	char	*str;

	n = num;
	len = calculate_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	set_char(str, len - 1, n);
	return (str);
}
