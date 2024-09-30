/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:10:03 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/06 13:53:53 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node;

	if (!lst)
		return ;
	node = lst;
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}

/* void	f(void *content)
{
	*(char *)content = '5';
}

int	main(void)
{
	t_list	*lst;
	t_list	**test;

	lst = 0;
	test = &lst;
	ft_lstadd_back(test, ft_lstnew("hola"));
	ft_lstadd_back(test, ft_lstnew("adios"));
	lst = *test;
	printf("%s\n", (char *)lst->content);
	ft_lstiter(lst, f);
	printf("%s\n", (char *)lst->content);
	return (0);
} */
