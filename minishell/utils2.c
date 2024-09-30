/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:35:35 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/30 11:10:57 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funcion que chequea si es un numero o  caracter especial
int	special_digit(int i)
{
	if (i == '*' || i == '@' || i == 92)
		return (1);
	else if (i < '0' || i > '9')
		return (0);
	return (1);
}

//funcion que chequea si hay un digito despues de un dolar
//para despues quitarlos
int	check_dolar_and_digit(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && s[i] != '$')
	{
		if (s[i] && s[i] == '$' && s[i + 1] && special_digit(s[i + 1]) == 1)
			return (1);
		i++;
	}
	return (0);
}

//funcion que chequea si despues de la variable
//hay un caracter especial,  ya que cambia la interpretacion de la variable
int	check_special_char(char c)
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~' || c == '?'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$'
		|| c == ';' || c == '\\')
		return (-1);
	return (0);
}

//funcion para buscar el siguiente caracter que no este entre comillas
int	search_next_char(char *s, char c, int j)
{
	int	i;

	i = -1;
	while (s[++i] && s[i + 1])
	{
		if (s[i] == 34)
		{
			while (s[++i] != 34)
				if (s[i] == '$' && i >= j)
					return (i);
		}
		if (s[i] == 39)
		{
			i++;
			i = get_next_quote(i, s, 39);
		}
		if (s[i] == c && i >= j)
			return (i);
	}
	return (0);
}

char	*cmd_name_var(t_cmd *cmd, char *line, char *name_var)
{
	int		i;
	char	*result;

	i = -1;
	while (++i < cmd->env->num_env)
	{
		if (var_strcmp(name_var, cmd->env->env[i]) == 0)
		{
			free(name_var);
			result = ft_add_var_value(cmd->env->env[i]);
			return (change_line_value(line, result));
		}
		else if (i + 1 == cmd->env->num_env)
		{
			free(name_var);
			return (change_line_value(line, ft_strdup("")));
		}
	}
	return (0);
}
