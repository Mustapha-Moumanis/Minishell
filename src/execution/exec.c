/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:34:26 by shilal            #+#    #+#             */
/*   Updated: 2023/05/23 11:26:58 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	first_cmd(t_exec *val)
{
	if (val->tmp->out_file == 1)
		val->tmp->out_file = val->pe[val->n_p][1];
	if (builtins(val) == 1)
	{
		val->fork = fork();
		if (val->fork == -1)
			return (ft_error("fork fail\n"));
		else if (val->fork == 0)
		{
			dup2(val->tmp->in_file, 0);
			if (val->tmp->out_file != 1)
				dup2(val->tmp->out_file, 1);
			else
				dup2(val->pe[val->n_p][1], 1);
			ecx(val, get_path(val->env));
		}
	}
	close(val->pe[val->n_p][1]);
	val->tmp = val->tmp->next;
	return (0);
}

int	last_cmd(t_exec *val)
{
	int	i;

	i = 0;
	if (builtins(val) == 1)
	{
		val->fork = fork();
		if (val->fork == -1)
			return (ft_error("fork fail\n"));
		if (val->fork == 0)
		{
			dup2(val->tmp->out_file, 1);
			if (val->tmp->in_file != 0)
				dup2(val->tmp->in_file, 0);
			else
				dup2(val->pe[val->n_p][0], 0);
			ecx(val, get_path(val->env));
		}
	}
	while (wait(NULL) > 0)
		i++;
	close(val->pe[val->n_p][0]);
	return (0);
}

int	other_commands(t_exec *val)
{
	while (val->tmp->next)
	{
		val->tmp->out_file = val->pe[val->n_p + 1][1];
		if (builtins(val) == 1)
		{
			val->fork = fork();
			if (val->fork == -1)
				return (ft_error("fork fail\n"));
			else if (val->fork == 0)
			{
				if (val->tmp->in_file != 0)
					dup2(val->tmp->in_file, 0);
				else
					dup2(val->pe[val->n_p][0], 0);
				if (val->tmp->out_file != 1)
					dup2(val->pe[val->n_p + 1][1], 1);
				ecx(val, get_path(val->env));
			}
		}
		close(val->pe[val->n_p][0]);
		close(val->pe[val->n_p + 1][1]);
		val->tmp = val->tmp->next;
		val->n_p++;
	}
	return (0);
}

int	exc_comande(t_exec *val)
{
	val->n_p = 0;
	val->pe = (int **)malloc((val->size - 1) * sizeof(int *));
	if (!val->pe)
	{
		free(val->pe);
		return (2);
	}
	if (init_pipes(val->size - 1, val->pe) == 2)
	{
		free(val->pe);
		return (2);
	}
	else
	{
		if (first_cmd(val) != 2)
		{
			if (other_commands(val) != 2)
			{
				if (last_cmd(val) != 2)
					return (0);
			}
		}
		return (2);
	}
	return (0);
}
