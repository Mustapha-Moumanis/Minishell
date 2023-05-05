/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:59:00 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/05 16:35:00 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sp_builtins(t_exec *val, t_data *data)
{
	val->check = data->head->full_cmd[0];
	if (val->check)
	{
		str_lowercase(val->check);
		if (ft_strcmp(val->check, "echo") == 0)
			echo(val, data);
		else if (ft_strcmp(val->check, "pwd") == 0)
			pwd(val, data);
		else if (ft_strcmp(val->check, "env") == 0)
			env(val, data);
		else
			val->onther = 1;
	}
}

void	builtins(t_exec *val, t_data *data)
{
	if (ft_strcmp(data->head->full_cmd[val->i], "cd") == 0)
		cd(val, data);
	else if (ft_strcmp(data->head->full_cmd[val->i], "export") == 0)
		export(val, data);
	else if (ft_strcmp(data->head->full_cmd[val->i], "unset") == 0)
		echo(val, data);
	else if (ft_strcmp(data->head->full_cmd[val->i], "exit") == 0)
		echo(val, data);
	else
		sp_builtins(val, data);
}

void	exuct(t_data *data, t_exec *val)
{
	val->onther = 0;
	val->i = 0;
	builtins(val, data);
	if (val->onther == 1)
		printf("Onther command\n");
}
