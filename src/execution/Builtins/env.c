/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 07:28:46 by shilal            #+#    #+#             */
/*   Updated: 2023/05/14 00:26:06 by shilal           ###   ########.fr       */
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
	}
	else
		ft_putendl_fd("Error", 2);
}
