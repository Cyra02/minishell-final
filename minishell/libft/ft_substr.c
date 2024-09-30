/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:03:38 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/04 15:02:59 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*r;

	i = 0;
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	r = malloc(sizeof(char) * (len + 1));
	if (r == NULL)
		return (NULL);
	while (i < len)
	{
		r[i] = s[start];
		start++;
		i++;
	}
	r[i] = '\0';
	return (r);
}

/*int	main(void)
{
	char	s[] = "hola que tal";

	printf ("%s", ft_substr(s, 5, 13));
}
*/