/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 07:19:55 by shilal            #+#    #+#             */
/*   Updated: 2023/05/02 13:54:11 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pwd(t_exec *val, t_data *data)
{
	if (getcwd(val->cd_path, 1024))
	{
		ft_putendl_fd(val->cd_path, data->head->out_file);
	}
	else
	{
		val->pos_path += 1;
		ft_putendl_fd(val->last_path, data->head->out_file);
	} 
}
