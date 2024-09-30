/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:18:38 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/03 11:14:18 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int	r;

	r = 0;
	while (lst)
	{
		lst = lst->next;
		r++;
	}
	return (r);
}

/*int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew("hola que tal");
	printf("%d\n", ft_lstsize(lst));
	return (0);
}
*/