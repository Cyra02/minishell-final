/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:24:27 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/30 11:13:02 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

void	recive_args(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell>");
		if (input == NULL)
			exit_error("exit", g_error);
		if (check_spaces(input) == -1 || input[0] == '\0')
		{
			free(input);
			continue ;
		}
		else
		{
			add_history(input);
			if (check_lines(shell, &shell->cmd, input)
				&& shell->flags->quote != 0)
			{
				if (check_nonpipas(shell->cmd, noquotes(shell->cmd->cmd)))
					execute_nopipas(shell->cmd, noquotes(shell->cmd->cmd));
				else
					execute_cmd(&(shell->cmd), init_pipes(), 1);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc != 1)
		many_args(argv);
	g_error = 0;
	shell = init(envp);
	wait_signal(1);
	recive_args(shell);
	return (0);
}
