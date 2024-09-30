/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:13:13 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/26 13:00:39 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_alph(char **temp)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = temp[0];
	if (!temp[i + 1])
	{
		temp[0] = NULL;
	}
	while (temp[i])
	{
		if (ft_strncmp(res, temp[i], ft_strlen(res)) > 0)
		{
			res = temp[i];
			j = i;
		}
		i++;
	}
	temp[j] = temp[i - 1];
	temp[i - 1] = NULL;
	return (res);
}

char	*add_quotes(char *s)
{
	int		i;
	char	*res;

	i = -1;
	res = ft_calloc(sizeof(char), ft_strlen(s) + 3);
	if (!res)
		exit_error("Error Malloc", 51);
	while (s[++i])
	{
		res[i] = s[i];
		if (s[i] == '=')
		{
			res[i + 1] = 34;
			break ;
		}
	}
	while (s[++i])
	{
		res[i + 1] = s[i];
	}
	res[i + 1] = 34;
	res[i + 2] = '\0';
	free(s);
	return (res);
}

int	count_env(char **arg, int len)
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

char	**check_ord(char **res, t_cmd *cmd)
{
	int		i;
	char	**temp;
	int		num;

	num = count_env(cmd->env->env, cmd->env->num_env);
	temp = convert_to_env(cmd->env->env, num);
	i = 0;
	if (num - i)
	{
		res[i++] = first_alph(temp);
	}
	free (temp);
	return (res);
}

void	export_var(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->env->num_env)
	{
		if (cmd->env->env[i] != NULL)
		{
			printf("declare -x %s\n", cmd->env->env[i]);
		}
		i++;
	}
}
/*
void	export_var(t_cmd *cmd)
{
	int		i;
	char	**res;

	i = 0;
	printf("%i", cmd->env->num_env);
	res = ft_calloc(sizeof(char *), cmd->env->num_env + 1);
	if (!res)
		exit_error("Error Malloc", 28);
	res = check_ord(res, cmd);
	while (res[i])
	{
		if (res[i] != NULL)
		{
			res[i] = add_quotes(res[i]);
			printf("declare -x %s\n", res[i]);
		}
		free (res[i]);
		i++;
	}
	free (res);
}*/
