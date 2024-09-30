/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:51:17 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/09 10:37:35 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

/* void	del(void *content)
{
	*(char *) content = 0;
	free (content);
}

int	main(void)
{
	t_list	*lst;
	t_list	**test = malloc (sizeof(t_list *));

	ft_lstadd_back(test, ft_lstnew(ft_strdup("hola")));
	ft_lstadd_back(test, ft_lstnew(ft_strdup("adios")));
	lst = *test;
	printf("%d\n", ft_lstsize(lst));
	ft_lstdelone((lst->next), del);
	printf("%s\n", lst->next->content);
	lst->next = NULL; 
	printf("%d\n", ft_lstsize(lst));
	return (0);
}
 */