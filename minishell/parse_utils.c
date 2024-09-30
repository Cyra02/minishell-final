/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:26:16 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/30 11:11:45 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funcion que cuenta el numero de argumentos
int	ft_count_args(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i])
	{
		if ((str[i] != 32 && str[i] != 34 && str[i] != 39)
			&& (str[i + 1] == 32 || str[i + 1] == '\0'
				|| str[i + 1] == 34 || str[i + 1] == 39))
			res++;
		if (str[i] == 34 || str[i] == 39)
		{
			res++;
			i = get_next_quote(i + 1, str, str[i]);
		}
	}
	return (res);
}

//funcion que obtiene el siguiente quote
int	get_next_quote(int i, char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

//funcion que obtiene el siguiente espacio
int	ft_check_quote_pair(char *input, int *i, char quote)
{
	int	count;

	count = 1;
	while (input[*i + 1] && input[*i + 1] != quote)
		(*i)++;
	if (input[*i + 1] == quote)
		count++;
	(*i)++;
	return (count);
}

int	ft_check_quote(char *input, int simple, int doble, t_shell *shell)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == 34)
			doble += ft_check_quote_pair(input, &i, input[i]);
		if (input[i] == 39)
			simple += ft_check_quote_pair(input, &i, input[i]);
		if (doble % 2 != 0 || simple % 2 != 0)
		{
			shell->flags->quote = 1;
			printf("error quotes\n");
			return (0);
		}
	}
	return (1);
}

int	start_line(t_shell **shell, char *input, char ***lines)
{
	(*shell)->flags->quote = ft_check_quote(input, 2, 2, (*shell));
	if ((*shell)->flags->quote == 0)
	{
		free(input);
		return (1);
	}
	(*shell)->flags->pipe = ft_count_pipes(input);
	if ((*shell)->flags->pipe == -1)
	{
		free(input);
		return (1);
	}
	*lines = ft_split_pipes(input);
	if (!(*lines))
	{
		free(input);
		return (1);
	}
	return (0);
}
