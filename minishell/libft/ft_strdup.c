/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:10:54 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/25 12:10:54 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = (char *)ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	return (ft_memcpy(str, s, len));
}

/*int	main(void)
{
	char s1[] = "hola que tal";

	printf("%s\n", s1);
}
*/