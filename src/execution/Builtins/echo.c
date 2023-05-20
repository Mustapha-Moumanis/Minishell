/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:32:21 by shilal            #+#    #+#             */
/*   Updated: 2023/05/20 14:23:39 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	n_line(char **str, t_exec *n)
{	
	while (str[n->i] && strcmp(str[n->i], "-n") == 0)
		n->i++;
}

void	echo(t_exec *val)
{
	int	nl;

	val->i++;
	nl = 0;
	if (val->tmp->full_cmd[val->i])
	{
		if (strcmp(val->tmp->full_cmd[val->i], "-n") == 0)
		{
			n_line(val->tmp->full_cmd, val);
			nl = 1;
		}
		while (val->tmp->full_cmd[val->i])
		{
			ft_putstr_fd(val->tmp->full_cmd[val->i], val->tmp->out_file);
			val->i++;
		}
		if (nl == 0)
			ft_putstr_fd("\n", val->tmp->out_file);
	}
	else
		ft_putstr_fd("\n", val->tmp->out_file);
}
