/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:44:07 by aule86            #+#    #+#             */
/*   Updated: 2024/09/26 13:34:31 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_error = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
		g_error = 130;
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
		g_error = 131;
	}
	return ;
}

void	wait_signal(int i)
{
	struct sigaction	sa;

	if (i)
		sa.sa_handler = &signal_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
