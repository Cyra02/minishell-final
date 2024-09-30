/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:11:42 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/30 11:14:01 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funcion que crea una variable con el nombre que tiene el argumento
//que manden con $ para luego compararla con las variables de entorno

char	*ft_name_var(char *line)
{
	int		i;
	int		j;
	char	*res;

	i = get_next_quote(0, line, '$') + 1;
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && check_special_char(line[i + j]) == 0)
		j++;
	res = ft_calloc(sizeof(char), j + 1);
	if (!res)
		exit_error("Error malloc", 16);
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && check_special_char(line[i + j]) == 0)
	{
		res[j] = line[i + j];
		j++;
	}
	return (res);
}
//funcion que retorna el resto de una variable si hay caracteres especiales
//ej: echo "$USER@hola" -> @hola

char	*ft_split_var(char *str, int i, t_cmd *cmd)
{
	int		j;
	char	*res;

	cmd->flags->dollar_special = 1;
	j = i;
	while (str[i])
		i++;
	res = malloc(sizeof(char) * i - j + 1);
	if (!res)
		exit_error("Error malloc", 17);
	i = 0;
	while (str[j])
	{
		res[i] = str[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_change_var(t_cmd *cmd, char *s, char **var_reminder)
{
	char	*name_var;
	int		i;

	if (ft_strnstr(s, "$?", ft_strlen(s)) != 0)
		return (ft_replace_value(s));
	name_var = ft_name_var(s);
	i = search_next_char(s, '$', -1);
	while (s[++i] && s[i] != ' ')
	{
		if ((check_special_char(s[i]) == -1
				&& s[i] != '$') || (s[i] == '$'
				&& i == search_next_char(s, '$',
					search_next_char(s, '$', -1) + 1)))
		{
			*var_reminder = ft_split_var(s, i, cmd);
			break ;
		}
	}
	if (!name_var)
		return (NULL);
	if (!name_var[0])
		return (ft_strchr(s, '$') + 1);
	return (cmd_name_var(cmd, s, name_var));
}

//Reemplaza las ocurrencias de variables precedidas por '$'
// en la cadena `s` con sus valores correspondientes.
char	*change_dolar_x_var(t_cmd *cmd, char *s, char *var_reminder)
{
	char	*temp;

	if (check_dolar_and_digit(s) == 0)
		s = quit_dollar_and_digit(s, -1, -1);
	if (check_dolar(s) == 0)
		return (s);
	cmd->flags->dollar_special = 0;
	s = ft_change_var(cmd, s, &var_reminder);
	if (check_dolar(s) == 1)
		s = change_dolar_x_var(cmd, s, NULL);
	if (cmd->flags->dollar_special == 1)
	{
		temp = ft_strjoin_special(s, var_reminder, 0, 0);
		free(s);
		s = temp;
		free(var_reminder);
		var_reminder = NULL;
		cmd->flags->dollar_special = 0;
	}
	if (check_dolar(s) == 1)
		return (change_dolar_x_var(cmd, s, NULL));
	if (var_reminder)
		free(var_reminder);
	return (s);
}
