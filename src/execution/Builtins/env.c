/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 07:28:46 by shilal            #+#    #+#             */
/*   Updated: 2023/05/03 18:18:36 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env(t_exec *val, t_data *data)
{
	t_env	*tmp;

	val->i++;
	if (!data->head->full_cmd[val->i])
	{
		tmp = val->env;
		while (tmp)
		{
			ft_putstr_fd(tmp->name, data->head->out_file);
			ft_putchar_fd('=', data->head->out_file);
			ft_putendl_fd(tmp->value, data->head->out_file);
			tmp = tmp->next;
		}
	}
	else
		ft_putendl_fd("Error", 2);
}
