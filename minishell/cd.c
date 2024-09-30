/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:58:56 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/27 13:32:49 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	value_pwd(char *s, t_cmd *cmd, int control)
{
	int		i;
	char	*temp;

	i = -1;
	s = actual_path(0);
	while (++i < cmd->env->num_env)
	{
		if (control == 0 && cmd->env->env[i]
			&& !ft_strncmp(cmd->env->env[i], "OLDPWD", 6))
		{
			temp = ft_strjoin("OLDPWD=", s, 2);
			free(cmd->env->env[i]);
			cmd->env->env[i] = temp;
		}
		if (control == 1 && cmd->env->env[i]
			&& !ft_strncmp(cmd->env->env[i], "PWD", 3))
		{
			temp = ft_strjoin("PWD=", s, 2);
			free(cmd->env->env[i]);
			cmd->env->env[i] = temp;
		}
	}
	free(s);
}

int	ft_cd(t_cmd **cmd)
{
	char	*temp;

	value_pwd(NULL, (*cmd), 0);
	if ((*cmd)->num_arg == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	temp = noquotes((*cmd)->arg[0]);
	if (!ft_strncmp(temp, "-", 2))
		chdir(getenv("OLDPWD"));
	else if (chdir(temp) == -1)
		put_error("bash: cd", temp, "No such file or directory\n");
	else
	{
		free(temp);
		value_pwd(NULL, (*cmd), 1);
		return (0);
	}
	free(temp);
	return (1);
}
