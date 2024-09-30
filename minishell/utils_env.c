/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:34:16 by aule86            #+#    #+#             */
/*   Updated: 2024/09/27 13:32:06 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wrong_exp(char c)
{
	if (c == '?' || c == '!' || c == '.'
		|| c == '+' || c == '}' || c == '{' || c == '-' || c == 92
		|| c == '[' || c == ']' || c == '@' || c == '*' || c == '#'
		|| c == '^' || c == '~')
	{
		return (1);
	}
	return (0);
}

// funcion que reemplaza el ~ por el home
char	*replace_prime(char *s)
{
	char	*res;
	char	*temp;
	char	*temp2;

	temp = ft_strdup(s + 1);
	res = ft_strdup(getenv("HOME"));
	if (!res)
		exit_error("Error malloc", 50);
	temp2 = ft_strjoin(res, temp, 2);
	free(res);
	free(temp);
	return (temp2);
}

int	check_prime(char *s)
{
	if (s && s[0] == '~' && (!s[1] || s[1] == '/'))
		return (1);
	return (0);
}

// mira que haya algun charater que no sea espacio
int	check_spaces(char *c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (c[++i])
	{
		if (c[i] == '\t' || c[i] == '\n'
			|| c[i] == '\v' || c[i] == '\f'
			|| c[i] == '\r' || c[i] == ' ')
			j++;
	}
	if (j == i)
		return (-1);
	return (0);
}

//funcion para contar todas las variables de entorno que no sean nulas.
int	ft_count_env(char **arg, int len)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (j < len)
	{
		if (arg[j] == NULL)
			i++;
		j++;
	}
	return (j - i);
}
