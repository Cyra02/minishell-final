/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:52:59 by aule86            #+#    #+#             */
/*   Updated: 2024/09/26 13:52:47 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funcion para añadir el valor de la variable de entorno
//a la variable res
char	*ft_add_var_value(char *s1)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(s1) - i + 1));
	if (!res)
		exit_error("Error malloc", 17);
	while (s1[++j])
		res[j - 1] = s1[i + j];
	res[j] = '\0';
	return (res);
}

// funcion recursiva que quita el dolar y el digito sobrantes
//ej: $12aa $34bb -> aa bb
char	*quit_dollar_and_digit(char *s, int i, int j)
{
	char	*res;

	while (s[++i])
	{
		if (s[i] && s[i] == '$' && s[i + 1]
			&& special_digit(s[i + 1]) == 1)
		{
			j = -1;
			res = malloc(sizeof(char) * ft_strlen(s) - 1);
			if (!res)
				exit_error("Error malloc", 15);
			while (++j < i)
				res[j] = s[j];
			i++;
			while (s[++i])
			{
				res[j] = s[i];
				j++;
			}
			res[j] = '\0';
			free(s);
			s = quit_dollar_and_digit(res, -1, -1);
		}
	}
	return (s);
}

char	*ft_craft_result(char *line_final, char *line, char *var, int c)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = search_next_char(line, '$', -1);
	if ((size_t)k == ft_strlen(line))
		return (line);
	while (++i < k)
		line_final[i] = line[i];
	while (var[++j])
		line_final[i + j] = var[j];
	while (line[i + c])
	{
		line_final[i + j] = line[i + c];
		i++;
	}
	line_final[i + j] = '\0';
	return (line_final);
}

//funcion que cambia el valor de la linea y sustituye el $var
//por el valor de la variable de entorno
char	*change_line_value(char *line, char *var)
{
	int		i;
	int		j;
	char	*res;

	j = 0;
	i = search_next_char(line, '$', -1);
	while (line[i + j] && line[i + j] != ' '
		&& line[i + j] != 34 && line[i + j] != 39)
		j++;
	while (line[i + j])
		i++;
	res = malloc(sizeof(char) * i + ft_strlen(var));
	if (!res)
		exit_error("Error malloc", 18);
	res = ft_craft_result(res, line, var, j);
	free(line);
	free(var);
	return (res);
}

void	expand(t_cmd **cmd)
{
	int		i;

	i = -1;
	if (check_dolar((*cmd)->cmd) == 1)
		(*cmd)->cmd = change_dolar_x_var((*cmd), (*cmd)->cmd, NULL);
	if (check_prime((*cmd)->cmd) == 1)
		(*cmd)->cmd = replace_prime((*cmd)->cmd);
	if (!(*cmd)->arg)
		return ;
	while ((*cmd)->arg[++i])
	{
		if (check_dolar((*cmd)->arg[i]) == 1)
			(*cmd)->arg[i] = change_dolar_x_var((*cmd), (*cmd)->arg[i], NULL);
		if (check_prime((*cmd)->arg[i]) == 1)
			(*cmd)->arg[i] = replace_prime((*cmd)->arg[i]);
	}
}
