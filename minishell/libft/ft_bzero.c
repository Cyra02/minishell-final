/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:16:36 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/04 16:19:28 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = s;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
}

/*int	main(void)
{
	char	s[] = "hola";

	printf("%s\n", s);
	ft_bzero(s, 0);
	printf("%s\n", s);
	ft_bzero(s, 5);
	printf("%s\n", s);
}
*/