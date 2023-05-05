/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:32:21 by shilal            #+#    #+#             */
/*   Updated: 2023/04/15 15:41:36 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	n_line(char **str, t_exec *n)
{	
	while (strcmp(str[n->i], "-n") == 0)
		n->i++;
}

void	echo(t_exec *val, t_data *data)
{
	int	nl;

	val->i++;
	nl = 0;
	if (data->head->full_cmd[val->i])
	{
		if (strcmp(data->head->full_cmd[val->i], "-n") == 0)
		{
			n_line(data->head->full_cmd, val);
			nl = 1;
		}
		while (data->head->full_cmd[val->i])
		{
			ft_putstr_fd(data->head->full_cmd[val->i], data->head->out_file);
			val->i++;
		}
		if (nl == 0)
			ft_putstr_fd("\n", data->head->out_file);
	}
	else
		ft_putstr_fd("\n", data->head->out_file);
}
