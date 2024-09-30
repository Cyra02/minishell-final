/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:54 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/03 11:55:38 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

/*int	main(void)
{
	t_list	**lst;
	t_list	*node;

	node = 0;
	lst = &node;
	*lst = ft_lstnew("hola que tal");
	ft_lstadd_back(lst, ft_lstnew("bien y tu"));
	node = *lst;
	while (node)
	{
		printf("%s\n", (char *) node->content);
		node = node->next;
	}
	return (0);
}
*/
