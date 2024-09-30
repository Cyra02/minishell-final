/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciestrad <ciestrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:30:22 by aule86            #+#    #+#             */
/*   Updated: 2024/09/13 13:34:55 by ciestrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	many_args(char **argv)
{
	size_t	len;

	len = ft_strlen(argv[0]);
	if (ft_strlen(argv[0]) < ft_strlen(argv[1]))
		len = ft_strlen(argv[1]);
	if (ft_strncmp(argv[0], argv[1], len) == 0)
		put_error(argv[0], argv[1], "cannot execute binary file");
	else
		put_error(argv[0], argv[1], "No such file or directory");
	exit(127);
}

//funcion que imprime el error y sale
void	exit_error(char *str, int n)
{
	printf("%s\n", str);
	exit(n);
}

//funcion que imprime el error
//bash: file: error
void	put_error(char *bash, char *file, char *error)
{
	ft_putstr_fd(bash, 2);
	ft_putstr_fd(": ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
		ft_putstr_fd(error, 2);
}

//funcion que libera un array
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clear_lst(t_cmd **cmd)
{
	t_cmd	*temp;
	t_cmd	*temp2;
	int		i;

	temp = *cmd;
	while (cmd && temp)
	{
		i = -1;
		temp2 = temp->next;
		free(temp->cmd);
		while (temp->arg && temp->arg[++i])
			free(temp->arg[i]);
		free(temp->arg);
		free(temp);
		temp = temp2;
	}
}
