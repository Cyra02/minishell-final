/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:23:52 by aule86            #+#    #+#             */
/*   Updated: 2024/09/06 11:21:15 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_file(int type, t_cmd *cmd, char *file)
{
	int		fd;

	if (type == 1 || type == 5)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error("Error open", 44);
	if (type == 5 || type == 6)
	{
		if (dup2(fd, cmd->pipe->out_error) == -1)
			exit_error("Error dup", 45);
	}
	else
	{
		if (dup2(fd, cmd->pipe->out) == -1)
			exit_error("Error dup", 45);
	}
	free(file);
	close(fd);
}

int	get_from_file(t_cmd *cmd, char *file, int i)
{
	int		fd;
	int		pfd[2];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		put_error("bash", file, "No such file or directory");
		pipe(pfd);
		if (dup2(pfd[1], cmd->pipe->out) == -1)
			exit_error("Error dup", 50);
		if (close(pfd[0]) == -1 || close(pfd[1]) == -1)
			exit_error("Error close", 51);
		while (cmd->arg[i])
			cmd->arg = remove_one(cmd->arg, i);
		free(file);
		return (1);
	}
	else if (dup2(fd, cmd->pipe->in) == -1)
		exit_error("Error dup", 45);
	close(fd);
	free(file);
	return (0);
}

void	get_input(t_cmd *cmd, char *stop)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error("Error pipe", 47);
	if (write(1, "> ", 2) == -1)
		exit_error("Error write", 48);
	line = get_next_line(cmd->pipe->in);
	while (line && ft_strncmp(line, stop, ft_strlen(stop)))
	{
		write(1, "> ", 2);
		if (write(fd[1], line, ft_strlen(line)) == -1)
			exit_error("Error write", 30);
		free(line);
		line = get_next_line(cmd->pipe->in);
	}
	free(line);
	free(stop);
	if (dup2(fd[0], cmd->pipe->in) == -1)
		exit_error("Error dup", 48);
	close(fd[0]);
	close(fd[1]);
}
