/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:00:28 by aule86            #+#    #+#             */
/*   Updated: 2024/09/27 13:32:29 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

// funcion que reemplaza el valor de $? por el valor de g_error
// en la cadena s, y devuelve la cadena resultante, liberando la cadena s
char	*ft_replace_value2(char *s, int i, int j)
{
	char	*res;
	char	*temp[3];

	temp[0] = ft_itoa(g_error);
	res = malloc(sizeof(char) * ((ft_strlen(s) - 1) + ft_strlen(temp[0])));
	if (!res)
		exit_error("Error malloc", 55);
	temp[1] = ft_substr(s, 0, i);
	temp[2] = ft_strdup(temp[1]);
	free(temp[1]);
	temp[1] = ft_strjoin("", temp[0], 2);
	free(temp[0]);
	temp[0] = ft_strjoin(temp[2], temp[1], 2);
	j = -1;
	while (temp[0][++j])
		res[j] = temp[0][j];
	while (s[++i] && s[i + 1])
		res[j++] = s[i + 1];
	res[j] = '\0';
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(s);
	return (res);
}

char	*ft_replace_value(char *s)
{
	int		i;
	int		j;

	i = get_next_quote(0, s, '?') - 1;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
			s = ft_replace_value2(s, i, -1);
		j = i;
		i = get_next_quote(0, s, '$');
		if (j == i)
			break ;
	}
	return (s);
}

//funcion strcmp modificada para variables de entorno
int	var_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s2[i] && s2[i] != '=')
		i++;
	if (ft_strlen(s1) != i)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

//funcion que chequea si hay un dolar
int	check_dolar(char *str)
{
	int	i;
	int	doubles;

	i = 0;
	doubles = 1;
	while (str[i])
	{
		if (str[i] == 39 && doubles == 1)
			i = get_next_quote(i + 1, str, str[i]);
		if (str[i] == 34)
			doubles *= -1;
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

//funcion que concatena $var con el valor de la variable de entorno
//siempre y cuando no haya caracteres especiales
char	*ft_strjoin_special(char *s1, char *s2, size_t i, size_t c)
{
	char	*str;
	size_t	size1;

	size1 = ft_strlen(s1);
	if (s1[size1 - 1] == 34 || s1[size1 -1] == 39)
		size1--;
	str = malloc(sizeof(char) * (size1 + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i] && i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[c])
	{
		str[i + c] = s2[c];
		c++;
	}
	str[i + c] = '\0';
	return (str);
}
