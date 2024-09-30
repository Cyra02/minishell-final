/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:09:57 by aule86            #+#    #+#             */
/*   Updated: 2024/09/19 11:19:25 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	newpipe(int *fd, int last)
{
	if (close(fd[0]) == -1)
		exit_error("Error close", 37);
	if (close(fd[1]) == -1)
		exit_error("Error close", 38);
	if (last)
		pipe(fd);
}

void	setpipes(t_pipe *pipes, int i)
{
	if (!pipes->last)
	{
		newpipe(pipes->fd[0], pipes->last);
		newpipe(pipes->fd[1], pipes->last);
	}
	else if (i % 2)
		newpipe(pipes->fd[1], pipes->last);
	else
		newpipe(pipes->fd[0], pipes->last);
}

static void	duppipe(int *io, int fd)
{
	if (close(*io) == -1)
		exit_error("Error close", 39);
	*io = dup(fd);
	if (*io == 1)
		exit_error("Error dup", 40);
}

void	setfds(t_pipe *pipe, int i)
{
	duppipe(&(pipe->in), STDIN_FILENO);
	duppipe(&(pipe->out), STDOUT_FILENO);
	if (i == 0)
		return ;
	else if (i % 2)
	{
		if (i != 1)
			duppipe(&(pipe->in), pipe->fd[1][0]);
		if (pipe->last)
			duppipe(&(pipe->out), pipe->fd[0][1]);
	}
	else
	{
		duppipe(&(pipe->in), pipe->fd[0][0]);
		if (pipe->last)
			duppipe(&(pipe->out), pipe->fd[1][1]);
	}
}

t_pipe	*init_pipes(void)
{
	t_pipe	*pipes;

	pipes = ft_calloc(sizeof(t_pipe), 1);
	if (pipe(pipes->fd[0]) == -1)
		exit_error("Error: pipe failed", 41);
	if (pipe(pipes->fd[1]) == -1)
		exit_error("Error: pipe failed", 42);
	pipes->in = dup(STDIN_FILENO);
	if (pipes->in == -1)
		exit_error("Error: dup failed", 43);
	pipes->out = dup(STDOUT_FILENO);
	if (pipes->out == -1)
		exit_error("Error: dup failed", 44);
	pipes->last = 1;
	pipes->out_error = STDERR_FILENO;
	return (pipes);
}
