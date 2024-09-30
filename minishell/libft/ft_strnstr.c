/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:30:37 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/05 16:57:04 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
	{
		return ((char *) haystack);
	}
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
			{
				return ((char *) &haystack[i]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

/*int	main(void)
{
	char	haystack [] = "hola que tal";
	char	needle [] = "bien y tu";

	printf("%s", ft_strnstr(haystack, needle, 8));
}
*/