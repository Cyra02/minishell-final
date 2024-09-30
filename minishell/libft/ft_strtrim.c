/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:05:17 by aszamora          #+#    #+#             */
/*   Updated: 2023/09/25 13:51:43 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	s1_len = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[s1_len]) && s1_len != 0)
		s1_len--;
	return (ft_substr((char *)s1, 0, s1_len + 1));
}

/*int	main(void)
{
	char	s1[] = "abhoalaab";
	char	set[] = "ab";

	printf("%s", ft_strtrim(s1, set));
}
*/