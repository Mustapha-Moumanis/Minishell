/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 07:28:46 by shilal            #+#    #+#             */
/*   Updated: 2023/05/05 23:25:27 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env(t_exec *val, t_data *data)
{
	t_env	*tm;

	val->i++;
	if (!data->head->full_cmd[val->i])
	{
		tm = val->env;
		while (tm)
		{
			ft_putstr_fd(tm->name, data->head->out_file);
			ft_putchar_fd('=', data->head->out_file);
			ft_putendl_fd(tm->value, data->head->out_file);
			tm = tm->next;
		}
	}
	else
		ft_putendl_fd("Error", 2);
}
