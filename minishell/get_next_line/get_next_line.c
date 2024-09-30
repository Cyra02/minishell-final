/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciestrad <ciestrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:17:57 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/13 13:57:57 by ciestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_find_nl(char *static_buff)
{
	unsigned int	i;

	if (!static_buff)
		return (-1);
	i = 0;
	while (static_buff[i] != '\n' && static_buff[i] != '\0')
		i++;
	if (static_buff[i] == '\0')
		return (-1);
	return (i);
}

char	*ft_finish_line(char *static_buff, int len)
{
	char	*line;
	int		i;

	line = (char *)malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (static_buff[i] != '\n')
	{
		line[i] = static_buff[i];
		i++;
	}
	line[i] = '\n';
	line [i + 1] = '\0';
	return (line);
}

char	*ft_line(char *static_buff)
{
	char	*line;
	int		len;

	if (ft_strlen_gnl(static_buff) <= 0)
		return (NULL);
	len = ft_find_nl(static_buff);
	if (len == -1 || len == ((int)ft_strlen_gnl(static_buff) - 1))
	{
		line = ft_strdup_gnl(static_buff);
		return (line);
	}
	line = ft_finish_line(static_buff, len);
	return (line);
}

char	*ft_static_buff(char *static_buff)
{
	int				i;
	unsigned int	len;

	if (!static_buff)
		return (NULL);
	len = ft_strlen_gnl(static_buff);
	i = ft_find_nl(static_buff);
	if (i == -1 || ((len - i) == 1))
	{
		free(static_buff);
		return (NULL);
	}
	static_buff = ft_substr_gnl(static_buff, (i + 1), (len - i - 1));
	return (static_buff);
}

char	*get_next_line(int fd)
{
	static char	*static_buff;
	char		*buffer;
	char		*line;
	int			bytes;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE +1);
	bytes = 1;
	while (ft_find_nl(static_buff) == -1 && buffer)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		read_error(&static_buff, &buffer, bytes);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		static_buff = ft_strjoin_gnl(static_buff, buffer);
	}
	free(buffer);
	if (bytes == -1 || !static_buff)
		return (NULL);
	line = ft_line(static_buff);
	static_buff = ft_static_buff(static_buff);
	return (line);
}

/* int main(void)
{
	int		fd;
	char	*line;

	fd = open("texto_prueba2.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
 */