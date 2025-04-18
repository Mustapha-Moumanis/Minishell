/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:55:59 by shilal            #+#    #+#             */
/*   Updated: 2023/06/03 22:37:29 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_pipes(int **pipe, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(pipe[i++]);
	}
	free(pipe);
}

int	init_pipes(int size, int **pe, t_exec *val)
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
			return (ft_error("malloc fail\n", val));
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (pipe(pe[i]) == -1)
			return (ft_error("pipe fail\n", val));
		i++;
	}
	return (0);
}

int	sp_builtins(t_exec *val)
{
	if (!val->tmp->full_cmd[0])
		return (2);
	val->check = ft_strdup(val->tmp->full_cmd[0]);
	str_lowercase(val->check);
	if (ft_strcmp(val->check, "echo") == 0)
		return (echo(val), free(val->check), 3);
	else if (ft_strcmp(val->check, "pwd") == 0)
		pwd(val);
	else if (ft_strcmp(val->check, "env") == 0)
		return (env(val), free(val->check), 3);
	else
		return (free(val->check), 1);
	free(val->check);
	return (0);
}

int	builtins(t_exec *val)
{
	int		i;

	val->i = 0;
	if ((ft_strcmp(val->tmp->full_cmd[val->i], "cd") == 0))
	{
		val->i++;
		if (val->size == 1 && val->tmp->in_file >= 0)
			return (cd(val));
	}
	else if ((ft_strcmp(val->tmp->full_cmd[val->i], "unset") == 0))
		return (unset(val), 3);
	else if (ft_strcmp(val->tmp->full_cmd[val->i], "exit") == 0)
		return (ft_exit(val), 3);
	else if (ft_strcmp(val->tmp->full_cmd[val->i], "export") == 0)
		return (export(val), 3);
	else
	{
		i = sp_builtins(val);
		if (i != 0)
			return (i);
	}
	return (0);
}

void	exuct(t_data *data, t_exec *val)
{
	val->tmp = data->head;
	val->size = ft_lstsize_h(val->tmp);
	if (!val->size)
		return ;
	if (val->size == 1)
	{
		if (val->tmp->in_file == -1 || val->tmp->out_file == -1)
			MY_EXIT_STATUS = 1;
		else if (one_cmd(val) == 2)
			MY_EXIT_STATUS = 1;
	}
	else
	{
		if (exc_comande(val) == 2)
			MY_EXIT_STATUS = 1;
		ft_free_pipes(val->pe, val->size - 1);
	}
}
