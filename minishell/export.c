/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:59:29 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/26 12:30:21 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_vars2(t_cmd **cmd, char *binary, int i, char **aux)
{
	int	j;

	j = -1;
	while (binary[++j])
	{
		if (binary[j] == '1')
		{
			aux[i] = ft_strdup((*cmd)->arg[j]);
			i++;
		}
	}
	free(binary);
	(*cmd)->env->env = aux;
}

int	new_vars1(t_cmd *cmd, char *binary)
{
	char	**aux;
	int		i;
	int		new_envs;

	i = -1;
	new_envs = 0;
	while (binary[++i])
		if (binary[i] == '1')
			new_envs++;
	aux = ft_calloc(sizeof(char *), (cmd->env->num_env + new_envs));
	if (!aux)
		exit_error("Error malloc", 24);
	i = -1;
	while (++i < cmd->env->num_env)
	{
		if (!cmd->env->env[i])
			aux[i] = NULL;
		else
			aux[i] = ft_strdup(cmd->env->env[i]);
		free(cmd->env->env[i]);
	}
	free(cmd->env->env);
	cmd->env->num_env = cmd->env->num_env + new_envs;
	new_vars2(&cmd, binary, i, aux);
	return (0);
}

int	ft_export(t_cmd **cmd)
{
	int		i;
	char	*res;
	char	*binary;

	i = -1;
	if (!(*cmd)->arg || !(*cmd)->arg[0])
	{
		export_var((*cmd));
		return (0);
	}
	while ((*cmd)->arg[++i] && i <= (*cmd)->num_arg)
	{
		res = noquotes((*cmd)->arg[i]);
		free((*cmd)->arg[i]);
		(*cmd)->arg[i] = res;
	}
	binary = malloc(sizeof(char) * (*cmd)->num_arg + 1);
	if (!binary)
		exit_error("Error malloc", 21);
	i = 0;
	if (export_parse((*cmd), binary, 0, 0) == -1)
		i = -1;
	new_vars1((*cmd), binary);
	return (i);
}
