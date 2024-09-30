/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:39:18 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/06 13:33:35 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		x = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = x;
	}
}

/*void	del(void *content)
{
	*(char *)content = 0;
}

int	main(void)
{
	t_list	*lst;
	t_list	**test;

	lst = 0;
	test = &lst;
	*test = ft_lstnew("lista1");
	ft_lstadd_back(test, ft_lstnew("lista2"));
	ft_lstadd_back(test, ft_lstnew("lista3"));
	lst = *test;
	printf("%d\n", ft_lstsize(lst));
	ft_lstdelone((test[0]), del);
	printf("%d\n", ft_lstsize(lst));
	return (0);
}
*/