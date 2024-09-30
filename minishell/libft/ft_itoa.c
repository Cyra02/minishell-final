/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:24:06 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/26 12:09:46 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	fill(char *str, int n)
{
	if (n == -2147483648)
		ft_strlcat(str, "-2147483648", 12);
	else if (n < 0)
	{
		str[0] = '-';
		fill(str, -n);
	}
	else if (n > 9)
	{
		fill(str, n / 10);
		fill(str, n % 10);
	}
	else
		str[ft_strlen(str)] = n + '0';
}

static int	unidad(int n)
{
	int	i;

	i = 2;
	if (n == -2147483648)
		return (12);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = ft_calloc(unidad(n), sizeof(char));
	if (!str)
		return (NULL);
	fill(str, n);
	return (str);
}

/*int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
}
*/