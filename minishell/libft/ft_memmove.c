/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:25:29 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/06 10:22:59 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	char			*s;
	char			*d;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (d);
}

/*int	main(void)
{
	char src[] = "hola!";
	char dest[] = "adios";

	printf("%s", ft_memmove(src, dest, 3));
	return (0);
}
*/