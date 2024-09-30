/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:44:42 by aule86            #+#    #+#             */
/*   Updated: 2024/09/03 11:22:09 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isdifoperator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

//funcion que obtiene el tipo de redireccion
int	redir_type(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = get_next_quote(i + 1, str, str[i]);
		if (str[i] == '>' && !isdifoperator(str[i + 1]))
			return (1);
		if (str[i] == '>' && str[i + 1] == '>' && !isdifoperator(str[i + 2]))
			return (2);
		if (str[i] == '<' && !isdifoperator(str[i + 1]))
			return (3);
		if (str[i] == '<' && str[i + 1] == '<' && !isdifoperator(str[i + 2]))
			return (4);
		if (str[i] == '2' && str[i + 1] == '>' && !isdifoperator(str[i + 2]))
			return (5);
		if (str[i] == '2' && str[i + 1] == '>' && str[i + 2] == '>')
			return (6);
		if (isdifoperator(str[i]))
			return (-1);
	}
	return (0);
}

int	is_redir(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (redir_type(arg[i]))
			return (i);
		i++;
	}
	return (-1);
}

//funcion que obtiene el caracter del operador
char	operator_char(int n)
{
	if (n == 1 || n == 2 || n == 5 || n == 6)
		return ('>');
	else if (n == 3 || n == 4)
		return ('<');
	return (0);
}

int	get_next_diff(int i, char *str)
{
	while (str[i] && !isdifoperator(str[i]))
		i++;
	return (i);
}
