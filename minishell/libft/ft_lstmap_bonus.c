/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:24:41 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/06 18:26:02 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*node;
	void	*content;

	if (!lst)
		return (NULL);
	node = 0;
	r = 0;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			del(content);
			ft_lstclear(&r, del);
			return (0);
		}
		ft_lstadd_back(&r, node);
		lst = lst->next;
	}
	return (r);
}
