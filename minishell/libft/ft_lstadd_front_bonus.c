/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:17:12 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/02 16:59:30 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		if (!lst)
		{
			*lst = new;
			return ;
		}
		else
		{
			new->next = *lst;
			*lst = new;
		}
	}
}

/*int	main(void)
{
	t_list	**lst;
	t_list	*node;

	node = 0;
	lst = &node;
	*lst = ft_lstnew("hola que tal");
	ft_lstadd_front(lst, ft_lstnew("bien y tu"));
	node = *lst;
	while (node)
	{
		printf("%s\n", (char *) node->content);
		node = node->next;
	}
	return (0);
}
*/