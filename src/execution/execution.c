/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:59:00 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/10 05:07:09 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipes(int size, int **pe);

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
			ecx(data->head->full_cmd, data->env);
	}
}

void	builtins(t_exec *val, t_data *data)
{
	val->onther = 0;
	val->i = 0;
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
	int	*pe;
	int	fr;
	int	i;

	val->size = ft_lstsize_h(data->head) - 1;
	i = val->size;
	pe = (int *)malloc(2 * sizeof(int));
	pipe(pe);
	fr = fork();
	if (fr == 0)
	{
		if (val->size == 0)
			builtins(val, data);
		close(pe[0]);
		dup2(pe[1], data->head->out_file);
		builtins(val, data);
	}
	waitpid(fr, NULL, 0);
	data->head = data->head->next;
	fr = fork();
	if (fr == 0)
	{
		close(pe[1]);
		dup2(pe[0], data->head->in_file);
		builtins(val, data);
	}
	close(pe[0]);
	close(pe[1]);
	waitpid(fr, NULL, 0);
}