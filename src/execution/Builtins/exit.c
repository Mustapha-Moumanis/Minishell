/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:29:01 by shilal            #+#    #+#             */
/*   Updated: 2023/05/29 13:50:49 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_erro_exit(char *str, char *arg)
{
	ft_putstr_fd("exit: ", 2);
	if (arg[0] != '\0')
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(str, 2);
	g_exit_status = 1;
}

int	check_arg_exit(char	*str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

void	arg_exit(t_exec *val)
{
	char	*s;
	int		nb;

	s = val->tmp->full_cmd[val->i];
	if (check_arg_exit(s))
	{
		if (val->tmp->full_cmd[val->i + 1])
			ft_erro_exit("too many arguments", "");
		else
		{
			nb = ft_atoi(s);
			if (nb >= 0 && nb <= 255)
				exit(nb);
			else
				exit (nb % 256);
		}
	}
	else
	{
		ft_erro_exit("numeric argument required", s);
		exit(255);
	}
}

void	ft_exit(t_exec *val)
{
	val->i++;
	if (val->size == 1 && val->tmp->in_file >= 0)
	{
		ft_putendl_fd("exit", val->tmp->out_file);
		if (val->tmp->full_cmd[val->i])
			arg_exit(val);
		else
			exit(1);
	}
}
