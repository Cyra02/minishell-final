/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:34:28 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/30 11:12:00 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

int	ft_count_pipes(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = get_next_quote(i + 1, str, str[i]);
		if ((str[i] == '|' && (str[i + 1] == '|' || str[i + 1] == '\0'))
			|| str[0] == '|')
		{
			put_error("bash", NULL, "syntax error near unexpected token `|'\n");
			g_error = 258;
			return (-1);
		}
		if (str[i] == '|')
			res++;
	}
	return (res);
}

char	**fill_memory(char *str, char **res)
{
	int	i;
	int	j;
	int	start;

	i = -1;
	j = 0;
	start = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = get_next_quote(i + 1, str, str[i]);
		if ((str[i + 1] == '|' || str[i + 1] == '\0') && str[i] != '|')
		{
			res[j] = ft_substr(str, start, i - start + 1);
			if (!res[j])
				exit_error("Error malloc", 53);
			j++;
		}
		if (str[i] == '|' && (str[i + 1] != '|' || str[i + 1] != '\0'))
			start = i + 1;
	}
	res[j] = NULL;
	return (res);
}

int	check_pipe_arg(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			res = 0;
	}
	if (res == -1)
		put_error("bash", NULL, "syntax error near unexpected token `|'\n");
	return (res);
}

//funcion que retorna el tipo de redireccion
int	check_redir(char **arg, int i)
{
	char	*temp;
	int		j;

	j = 0;
	if (redir_type(arg[i]) == -1)
	{
		put_error("bash", NULL, "syntax error near unexpected token `>'\n");
		return (-1);
	}
	temp = ft_strchr(arg[i], operator_char(redir_type(arg[i])));
	while (temp && redir_type(temp + j))
	{
		j = 0;
		while ((temp[j] && temp[j] == 32) || isdifoperator(temp[j]))
			j++;
		if ((redir_type(arg[i]) && !temp[j])
			|| isdifoperator(temp[ft_strlen(temp) - 1]))
		{
			put_error("bash", NULL, "syntax error near unexpected token `>'\n");
			return (-1);
		}
		temp = ft_strchr(temp + j, operator_char(redir_type(temp + j)));
	}
	return (0);
}

//checkea pipe y despues null
char	**ft_split_pipes(char *str)
{
	char	**res;
	int		i;

	i = -1;
	res = ft_calloc(sizeof(char *), (ft_count_pipes(str) + 2));
	if (!res)
		exit_error("Error malloc", 54);
	res = fill_memory(str, res);
	while (res[++i])
	{
		if (check_pipe_arg(res[i]) == -1 || check_redir(res, i) == -1)
		{
			g_error = 258;
			while (i >= 0)
				free(res[i--]);
			free(res);
			return (NULL);
		}
	}
	return (res);
}
