/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:32:21 by shilal            #+#    #+#             */
/*   Updated: 2023/05/31 20:21:27 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	str_is_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_exec *val)
{
	int	nl;

	val->i++;
	nl = 0;
	if (val->tmp->full_cmd[val->i] && val->tmp->full_cmd[val->i][0])
	{
		while (str_is_n(val->tmp->full_cmd[val->i]))
		{
			nl = 1;
			val->i++;
		}
		while (val->tmp->full_cmd[val->i])
		{
			ft_putstr_fd(val->tmp->full_cmd[val->i], val->tmp->out_file);
			if (val->tmp->full_cmd[val->i + 1])
				ft_putstr_fd(" ", val->tmp->out_file);
			val->i++;
		}
		if (nl == 0)
			ft_putstr_fd("\n", val->tmp->out_file);
	}
	else
		ft_putstr_fd("\n", val->tmp->out_file);
	g_exit_status = 0;
}
