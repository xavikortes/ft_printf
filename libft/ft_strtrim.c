/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:44:16 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/25 17:57:00 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	int		len;
	int		start;
	int		end;
	char	*new;

	if (str == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *) str);
	len = ft_strlen(str);
	start = 0;
	while (start < len && ft_strchr(set, str[start]))
		start++;
	end = len;
	while (end > start && ft_strchr(set, str[end - 1]))
		end--;
	new = ft_calloc(end - start + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str + start, end - start + 1);
	return (new);
}
