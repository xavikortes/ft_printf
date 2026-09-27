/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcortes <jcortes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:44:43 by jcortes           #+#    #+#             */
/*   Updated: 2026/09/24 17:46:49 by jcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	node = *lst;
	if (node == NULL)
		return ;
	next = node->next;
	ft_lstdelone(node, del);
	*lst = next;
	ft_lstclear(lst, del);
}
