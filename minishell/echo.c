/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:20:49 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/26 13:44:38 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	temp = noquotes(s);
	if (temp[i++] != '-')
		return (free(temp), 0);
	while (temp[i] == 'n')
		i++;
	if (temp[i])
		return (free(temp), 0);
	free(temp);
	return (1);
}

static void	echo_putstr(char *str, char *next)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == ';')
		{
			flag = 1;
			printf(" ");
		}
		if (str[i] != ';' && ft_isprint(str[i]))
			printf("%c", str[i]);
		i++;
	}
	if (next && *next && flag == 0)
	{
		printf(" ");
	}
	free(str);
}

int	ft_echo(t_cmd **cmd)
{
	int		i;
	int		x;
	char	*temp;

	if (!(*cmd)->arg && printf("\n"))
		return (0);
	i = 0;
	x = 1;
	while ((*cmd)->arg[i] && is_flag((*cmd)->arg[i]))
	{
		x = 0;
		i++;
	}
	while ((*cmd)->arg[i])
	{
		temp = noquotes((*cmd)->arg[i]);
		echo_putstr(temp, (*cmd)->arg[i + 1]);
		i++;
	}
	if (x)
		printf("\n");
	return (0);
}
