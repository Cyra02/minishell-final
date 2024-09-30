/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:28:13 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/03 11:27:55 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*int	main(void)
{
	t_list	*node;
	t_list	**list;

	node = 0;
	list = &node;
	ft_lstadd_back(list, ft_lstnew("pendejo"));
	ft_lstadd_front(list, ft_lstnew("tu madre"));
	ft_lstadd_front(list, ft_lstnew("chinga"));
	printf("%s\n", (char *)(ft_lstlast(*list)->content));
	return (0);
}
*/