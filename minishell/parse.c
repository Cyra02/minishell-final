/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:59:54 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/30 11:10:26 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_split_args(char *s, char **arg)
{
	int		i;
	int		start;
	int		pos;

	start = 0;
	pos = 0;
	i = -1;
	while (s[++i])
	{
		if ((s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			&& s[i + 1] && s[i + 1] != ' ')
			start = i + 1;
		if (s[i] == 34 || s[i] == 39)
			i = get_next_quote(i + 1, s, s[i]);
		if (s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13)
			&& (s[i + 1] == ' ' || s[i + 1] == '\0'))
		{
			arg[pos] = ft_substr(s, start, i - start + 1);
			if (arg[pos] == NULL)
				exit_error("Error malloc", 14);
			pos++;
		}
	}
	arg[pos] = NULL;
	return (i);
}

//funcion que obtiene el numero de argumentos
static char	**ft_get_args(t_shell *shell, char *input, t_cmd *cmd)
{
	char	**arg;
	char	*temp;

	temp = input;
	if (check_null_args(temp) == -1)
		temp = change_null_args(ft_strtrim(temp, " "), cmd);
	arg = malloc(sizeof(char *) * (cmd->num_arg + 1));
	if (!arg)
		exit_error("Error malloc", 13);
	shell->total_chars += ft_split_args(input, arg);
	if (check_null_args(input) == -1)
		free(temp);
	return (arg);
}

//funcion que obtiene el comando
static char	*get_command(t_shell *shell, char *input)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	while (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
		i++;
	start = i;
	while (input[i] && input[i] != 32 && !(input[i] >= 9 && input[i] <= 13)
		&& !isdifoperator(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
			i = get_next_quote(i + 1, input, input[i]);
		i++;
	}
	if (i && !isdifoperator(input[i]))
		str = ft_substr(input, start, i);
	else
		str = ft_strdup("CD");
	shell->total_chars += i;
	return (str);
}

//funcion que obtiene el siguiente quote
static t_cmd	*add_cmd(t_shell *shell, char *input)
{
	t_cmd	*temp;

	temp = ft_calloc(sizeof(t_cmd), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	temp->cmd = get_command(shell, input + shell->total_chars);
	temp->num_arg = ft_count_args(input + shell->total_chars);
	temp->next = NULL;
	temp->flags = shell->flags;
	temp->env = shell->env;
	if (temp->num_arg == 0)
		return (temp);
	temp->arg = ft_get_args(shell, input + shell->total_chars, temp);
	return (temp);
}

int	check_lines(t_shell *shell, t_cmd **cmd, char *input)
{
	int		i;
	t_cmd	*tmp;
	char	**lines;

	i = 0;
	lines = NULL;
	shell->total_chars = 0;
	if (start_line(&shell, input, &lines))
		return (0);
	*cmd = add_cmd(shell, lines[0]);
	expand(cmd);
	while (++i <= shell->flags->pipe)
	{
		shell->total_chars = 0;
		tmp = add_cmd(shell, lines[i]);
		expand(&tmp);
		(ft_last(cmd))->next = tmp;
		tmp = tmp->next;
	}
	while (i--)
		free(lines[i]);
	free(lines);
	free(input);
	return (1);
}
