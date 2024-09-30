/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:24:13 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/06 11:10:49 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, unsigned int dstsize)
{
	unsigned int	i;
	unsigned int	x;

	x = 0;
	i = 0;
	while (src[x] != '\0')
		x++;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < dstsize -1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}

/*int	main(void)
{
	char	dest [] = "hola";
	char	src [] = "hasta luego";

	printf(" %d| %s\n", ft_strlcpy(dest, src, 4), dest);
}
*/