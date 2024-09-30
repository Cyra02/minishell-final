/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:53:54 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/26 11:47:05 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*del_lst_var(char *s, int i)
{
	char	*res;
	int		j;

	j = 0;
	res = ft_calloc(sizeof(char), ft_strlen(s));
	if (!res)
		exit_error("Error malloc", 22);
	while (s[i])
	{
		if (wrong_exp(s[i]) == 0 && s[i] != '+' && s[i + 1] != '=')
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	free(s);
	return (res);
}

static int	parse_equal(char *s, int i)
{
	int	correct;

	correct = 0;
	while (s[i])
	{
		if (wrong_exp(s[i]) == 0 && s[i + 1] && s[i + 1] == '+'
			&& s[i + 2] && s[i + 2] == '=')
			return (-2);
		else if (s[i] == '!' && s[i + 1] && s[i + 1] != '=')
		{
			put_error("bash", s, "event not found\n");
			return (-1);
		}
		else if (wrong_exp(s[i]) == 1 || ft_isdigit(s[0]) == 1 || s[0] == 61)
		{
			put_error("bash: export", s, "not a valid identifier\n");
			return (-1);
		}
		if (s[i] == '=')
			correct++;
		i++;
	}
	if (correct == 0 || i == 1 || i == correct)
		return (-3);
	return (0);
}

static void	del_exist_variable(char *full_var, t_cmd *cmd, int i)
{
	char	*var;
	int		len;

	len = 0;
	if (full_var[0] == '=')
		return ;
	while (i < cmd->env->num_env)
	{
		while (cmd->env->env[i] == NULL && i < cmd->env->num_env)
			i++;
		if (i >= cmd->env->num_env)
			break ;
		var = cmd->env->env[i];
		len = get_next_quote(0, var, '=');
		if (!ft_strncmp(full_var, var, len + 1))
		{
			free(cmd->env->env[i]);
			cmd->env->env[i] = NULL;
		}
		i++;
	}
}

int	export_parse(t_cmd *cmd, char *array, int x, int flag)
{
	int	i;

	i = -1;
	while (cmd->arg[++i])
	{
		del_exist_variable(cmd->arg[i], cmd, 0);
		x = parse_equal(cmd->arg[i], 0);
		if (x == -2)
		{
			cmd->arg[i] = del_lst_var(cmd->arg[i], 0);
			del_exist_variable(cmd->arg[i], cmd, 0);
			array[i] = '1';
		}
		else if (x == -1)
		{
			array[i] = '0';
			flag = -1;
		}
		else if (x == -3)
			array[i] = '0';
		else
			array[i] = '1';
	}
	array[i] = '\0';
	return (flag);
}

char	**convert_to_env(char **arg, int len)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * len + 1);
	if (!res)
		exit_error("Error malloc", 27);
	i = 0;
	j = 0;
	while (j < len)
	{
		if (arg[j + i] && arg[j + i][0])
		{
			res[j] = ft_strdup(arg[i + j]);
			if (!res[j])
				exit_error("Error malloc", 35);
			j++;
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}
