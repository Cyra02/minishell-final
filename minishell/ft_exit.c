/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszamora <aszamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:30:03 by ciestrad          #+#    #+#             */
/*   Updated: 2024/09/30 11:09:04 by aszamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_error;

int	ft_atoi_error(int *atoi_error)
{
	*atoi_error = -1;
	return (-1);
}

static long long	ft_special_atoi(const char *str, int *atoi_error)
{
	int			i;
	int			result;
	long long	nbr;

	nbr = 0;
	i = 0;
	result = 1;
	if (ft_strlen(str) == 19
		&& (ft_strncmp("9223372036854775807", str, 20) < 0))
		return (ft_atoi_error(atoi_error));
	if ((ft_strlen(str) == 20 && ft_strncmp
			("-9223372036854775807", str, 21) < 0) || ft_strlen(str) > 20)
		return (ft_atoi_error(atoi_error));
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			result = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * result);
}

int	check_only_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9'))
		{
			put_error("exit\nbash: exit", s, "numeric argument required\n");
			exit (255);
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd, char *temp, int i)
{
	long long	n;
	int			atoi_error;

	if (cmd->arg && cmd->arg[0])
	{
		temp = noquotes(cmd->arg[0]);
		free(cmd->arg[0]);
		cmd->arg[0] = temp;
	}
	atoi_error = 0;
	if (cmd->num_arg == 0 || !cmd->arg[0])
		exit (g_error);
	else if (cmd->arg[1] && check_only_num(cmd->arg[0]))
		return (put_error("exit\nbash", "exit", "too many arguments\n"));
	while (cmd->arg[++i])
		check_only_num(cmd->arg[i]);
	n = ft_special_atoi(cmd->arg[0], &atoi_error);
	if (atoi_error == -1)
	{
		put_error("exit\nbash: exit", cmd->arg[0],
			"numeric argument required\n");
		exit (255);
	}
	printf("exit\n");
	exit ((unsigned char)n);
}
