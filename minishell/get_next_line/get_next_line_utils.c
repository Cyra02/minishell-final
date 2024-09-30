/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciestrad <ciestrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:39:34 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/13 13:58:40 by ciestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s )
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*r;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	len = ft_strlen_gnl(s1);
	r = (char *) malloc((len + 1) * sizeof(char));
	if (!r)
	{
		free(r);
		return (NULL);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*r;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen_gnl(s) < start)
		return (ft_strdup_gnl(""));
	if (len > ft_strlen_gnl(s + start))
		len = ft_strlen_gnl(s + start);
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
	{
		free(r);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		r[i] = s[start];
		start++;
		i++;
	}
	r[i] = '\0';
	free((char *)s);
	return (r);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	len1;
	unsigned int	len2;

	i = 0;
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
	{
		free(res);
		return (NULL);
	}
	while (i++ < len1)
		res[i - 1] = s1[i - 1];
	i = 0;
	while (i++ < len2)
		res[i - 1 + len1] = s2[i - 1];
	res[i - 1 + len1] = '\0';
	free((char *)s1);
	return (res);
}

void	read_error(char **static_buff, char **buffer, int bytes)
{
	if (bytes == -1)
	{
		free(*static_buff);
		free(*buffer);
		*static_buff = NULL;
		*buffer = NULL;
	}
}
