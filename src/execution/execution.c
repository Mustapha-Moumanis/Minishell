/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:59:00 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/21 11:26:47 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipes(int size, int **pe)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pe[i] = (int *)malloc(2 * sizeof(int));
		if (!pe[i])
		{
			while (--i >= 0)
				free(pe[i]);
			return (ft_error("malloc fail\n"));
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (pipe(pe[i]) == -1)
			return (ft_error("pipe fail\n"));
		i++;
	}
	return (0);
}

int	sp_builtins(t_exec *val)
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
			return (1);
		return (0);
	}
	return (2);
}

int	builtins(t_exec *val)
{
	int	i;
	
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
	{
		i = sp_builtins(val);
		if (i != 0)
			return (i);
	}
	return (0);
}

int	exuct(t_data *data, t_exec *val)
{
	int	fr;

	val->tmp = data->head;
	val->size = ft_lstsize_h(val->tmp);
	if (val->size == 1)
	{
		if (builtins(val) == 1)
		{
			fr = fork();
			if (fr == 0)
			{
				if (val->tmp->in_file != 0)
					dup2(val->tmp->in_file, 0);
				if (val->tmp->out_file != 1)
					dup2(val->tmp->out_file, 1);
				ecx(val, get_path(val->env));
			}
			waitpid(fr, NULL, 0);
		}
	}
	else
		return (exc_comande(val));
	return (0);
}
