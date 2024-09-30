/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:44:00 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/26 12:57:55 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->arg)
	{
		put_error("env", remove_quotes(cmd->arg[0], ';'),
			"No such file or Directory");
		return (127);
	}
	while (i < cmd->env->num_env)
	{
		if (cmd->env->env[i] != NULL)
			printf("%s\n", cmd->env->env[i]);
		i++;
	}
	return (0);
}
