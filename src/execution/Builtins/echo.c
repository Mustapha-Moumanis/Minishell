/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:32:21 by shilal            #+#    #+#             */
/*   Updated: 2023/05/28 19:20:28 by shilal           ###   ########.fr       */
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

void	n_line(char **str, t_exec *n)
{
	while (str[n->i] && str_is_n(str[n->i]))
		n->i++;
}

void	echo(t_exec *val)
{
	int	nl;

	val->i++;
	nl = 0;
	if (val->tmp->full_cmd[val->i] && val->tmp->full_cmd[val->i][0])
	{
		if (str_is_n(val->tmp->full_cmd[val->i]))
		{
			n_line(val->tmp->full_cmd, val);
			nl = 1;
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
