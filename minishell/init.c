/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:06:19 by aszamora          #+#    #+#             */
/*   Updated: 2024/09/27 13:45:43 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//inicializar env
static void	create_env(t_env *env, char **ev)
{
	char	**temp;
	int		i;
	char	*temp2;

	i = 0;
	while (ev[i])
		i++;
	env->num_env = i;
	temp = ft_calloc(i, sizeof(char *));
	if (!temp)
		exit_error("Error malloc", 3);
	while (--i >= 0)
	{
		temp[i] = ft_strdup(ev[i]);
		temp2 = ft_substr(temp[i], 5, ft_strlen(temp[i]) - 5);
		if (ft_strncmp(temp[i], "PATH=", 5) == 0)
			env->path = temp2;
		free(temp2);
	}
	if (!env->path)
		env->path = ft_strdup("./");
	env->env = temp;
}

//init estructura general
t_shell	*init(char **env)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		exit_error("Error malloc", 1);
	shell->bash_lvl = 2;
	shell->env = ft_calloc(sizeof(t_env), 1);
	if (!shell->env)
		exit_error("Error malloc", 2);
	create_env(shell->env, env);
	shell->flags = ft_calloc(sizeof(t_flags), 1);
	if (!shell->flags)
		exit_error("Error malloc", 4);
	return (shell);
}

t_cmd	*ft_last(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
