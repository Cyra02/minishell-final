/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:13:47 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/26 13:17:12 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*actual_path(int i)
{
	char	*s;
	char	*res;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		exit_error("Error malloc", 22);
	if (!getcwd(s, MAXPATHLEN))
		exit_error("Error malloc", 22);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		exit_error("Error malloc", 23);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[i] = '\0';
	return (res);
}

int	ft_pwd(int i)
{
	char	*s;
	char	*res;

	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	if (!s)
		exit_error("Error malloc", 22);
	if (!getcwd(s, MAXPATHLEN))
		return (10);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		exit_error("Error malloc", 23);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free (s);
	res[i] = '\0';
	if (write(1, &res[0], i + 1) != i + 1)
		return (-1);
	free(res);
	return (0);
}
