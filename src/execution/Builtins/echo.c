/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:32:21 by shilal            #+#    #+#             */
/*   Updated: 2023/06/03 03:00:41 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	str_is_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	echo(t_exec *val)
{
	int	nl;

	val->i++;
	nl = 0;
	if (val->tmp->full_cmd[val->i])
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
	MY_EXIT_STATUS = 0;
}
