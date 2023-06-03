/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 07:28:46 by shilal            #+#    #+#             */
/*   Updated: 2023/06/03 20:35:36 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env(t_exec *val)
{
	t_env	*tm;

	val->i++;
	if (!val->tmp->full_cmd[val->i])
	{
		tm = val->env;
		while (tm)
		{
			ft_putstr_fd(tm->name, val->tmp->out_file);
			ft_putchar_fd('=', val->tmp->out_file);
			ft_putendl_fd(tm->value, val->tmp->out_file);
			tm = tm->next;
		}
		g_exit_status = 0;
	}
	else
	{
		ft_putstr_fd("env : ", 2);
		ft_putstr_fd(val->tmp->full_cmd[val->i], 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_status = 1;
	}
}
