/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 07:28:46 by shilal            #+#    #+#             */
/*   Updated: 2023/04/15 14:23:56 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env(t_exec *val, t_data *data)
{
	int	i;

	val->i++;
	i = -1;
	if (!data->head->full_cmd[val->i])
	{
		while (data->env[++i])
			ft_putendl_fd(data->env[i], data->head->out_file);
	}
	else
		ft_putendl_fd("Error", 2);
}
