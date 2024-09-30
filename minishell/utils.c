/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:58:20 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/30 11:12:36 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str, char c)
{
	int		i;
	char	*temp;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] != c)
			size ++;
	}
	temp = malloc(sizeof(char) * size + 1);
	if (!temp)
		exit_error("Error malloc", 20);
	temp[size--] = '\0';
	while (--i >= 0)
	{
		if (str[i] != c)
		{
			temp[size] = str[i];
			size--;
		}
	}
	free(str);
	return (temp);
}

char	*str_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

//Recive una string y devuelve una copia sin las comillas que no correspondan
char	*noquotes(char *str)
{
	int		i;
	int		j;
	char	*temp;
	int		doubles;
	int		simples;

	i = -1;
	j = -1;
	doubles = 1;
	simples = 1;
	temp = ft_calloc(1, ft_strlen(str) + 1);
	if (!temp)
		exit_error("Error malloc", 11);
	while (str[++i])
	{
		if (str[i] == 34 && simples != -1)
			doubles = -doubles;
		else if (str[i] == 39 && doubles != -1)
			simples = -simples;
		else
			temp[++j] = str[i];
	}
	return (temp);
}

int	check_nonpipas(t_cmd *cmd, char *command)
{
	int	i;

	i = 0;
	if (cmd->next)
		i = 0;
	else if (!ft_strncmp(command, "export", 7))
		i = 1;
	else if (!ft_strncmp(command, "unset", 6))
		i = 1;
	else if (!ft_strncmp(command, "exit", 5))
		i = 1;
	else if (!ft_strncmp(command, "cd", 3))
		i = 1;
	free(command);
	return (i);
}

char	*atual_path(int i)
{
	char	*s;
	char	*temp;

	s = malloc(sizeof(char) * MAXPATHLEN + 1);
	if (!s)
		exit_error("ERROR MALLOC", 13);
	if (!getcwd(s, MAXPATHLEN))
		exit_error("ERROR MALLOC", 13);
	while (s[i])
		i++;
	temp = malloc(sizeof(char) * i + 1);
	if (!temp)
		exit_error("ERROR MALLOC", 13);
	i = -1;
	while (s[++i])
		temp[i] = s[i];
	free (s);
	temp[i] = '\0';
	return (temp);
}
