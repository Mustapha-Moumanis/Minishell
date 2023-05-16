/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:59:00 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/16 17:06:53 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sp_builtins(t_exec *val)
{
	val->check = val->tmp->full_cmd[0];
	if (val->check)
	{
		str_lowercase(val->check);
		if (ft_strcmp(val->check, "echo") == 0)
			echo(val);
		else if (ft_strcmp(val->check, "pwd") == 0)
			pwd(val);
		else if (ft_strcmp(val->check, "env") == 0)
			env(val);
		else
			val->onther = 1;
	}
}

void	builtins(t_exec *val)
{
	val->onther = 0;
	val->i = 0;
	if (ft_strcmp(val->tmp->full_cmd[val->i], "cd") == 0)
		cd(val);
	else if (ft_strcmp(val->tmp->full_cmd[val->i], "export") == 0)
		export(val);
	else if (ft_strcmp(val->tmp->full_cmd[val->i], "unset") == 0)
		unset(val);
	else if (ft_strcmp(val->tmp->full_cmd[val->i], "exit") == 0)
		echo(val);
	else
		sp_builtins(val);
}

void	exuct(t_data *data, t_exec *val)
{
	val->tmp = data->head;
	val->size = ft_lstsize_h(val->tmp);
	while (val->tmp)
	{
		builtins(val);
		if (val->onther != 0)
			printf("not_builtins\n");
		val->tmp = val->tmp->next;
	}
}
