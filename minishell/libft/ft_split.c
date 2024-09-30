/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:53:15 by aszamora          #+#    #+#             */
/*   Updated: 2023/10/06 13:52:45 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_words(char *str, char c)
{
	int	x;
	int	count;
	int	i;

	x = 0;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (str[i] == c)
			x = 0;
		i++;
	}
	return (count);
}

static void	freesplits(char **r)
{
	int	i;

	i = 0;
	while (r[i])
	{
		free(r[i]);
		i++;
	}
	free(r);
}

static size_t	mallocfail(char **r, size_t j)
{
	if (!r[j])
	{
		freesplits(r);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t			i;
	size_t			j;
	char			**r;
	unsigned int	start;

	i = 0;
	j = 0;
	r = ft_calloc(ft_words((char *)s, c) + 1, sizeof(char *));
	if (!r || !s)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (start < i)
		{
			r[j++] = ft_substr(s, start, i - start);
			if (!mallocfail(r, j - 1))
				return (0);
		}
	}
	return (r);
}

/* int	main(void)
{
	char	**splits;
	int		i;

	i = 0;
	splits = ft_split("hola que tal", ' ');
	while (splits[i])
	{
		printf("%s\n", splits[i]);
		i++;
	}
	return (0);
}
 */