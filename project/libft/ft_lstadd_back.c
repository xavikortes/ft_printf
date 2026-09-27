/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:39:50 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/24 17:40:13 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (lst == NULL || new == NULL)
		return ;
	node = *lst;
	if (node == NULL)
	{
		*lst = new;
		return ;
	}
	if (node->next == NULL)
	{
		node->next = new;
		return ;
	}
	return (ft_lstadd_back(&node->next, new));
}
