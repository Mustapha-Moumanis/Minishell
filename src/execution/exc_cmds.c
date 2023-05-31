/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:34:26 by shilal            #+#    #+#             */
/*   Updated: 2023/05/31 16:09:13 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	one_cmd(t_exec *val)
{
	val->j = builtins(val);
	if (val->j == 1)
	{
		signal(SIGINT, SIG_IGN);
		val->fork = fork();
		if (val->fork == -1)
			return (ft_error("fork fail\n"));
		else if (val->fork == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (val->tmp->in_file != 0)
				dup2(val->tmp->in_file, 0);
			if (val->tmp->out_file != 1)
				dup2(val->tmp->out_file, 1);
			ecx(val, get_path(val->env, "PATH"));
		}
		wait_procces();
	}
	else if (val->j == 0)
		g_exit_status = 0;
	return (val->j);
}

int	first_cmd(t_exec *val)
{
	int	j;

	if (val->tmp->out_file == 1)
		val->tmp->out_file = val->pe[val->n_p][1];
	j = builtins(val);
	if (j == 1 && val->tmp->in_file != -1 && val->tmp->out_file != -1)
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
			ecx(val, get_path(val->env, "PATH"));
		}
	}
	close(val->pe[val->n_p][1]);
	val->tmp = val->tmp->next;
	return (0);
}

int	last_cmd(t_exec *val)
{
	val->j = builtins(val);
	if (val->j == 1 && val->tmp->in_file != -1 && val->tmp->out_file != -1)
	{
		signal(SIGINT, SIG_IGN);
		val->fork = fork();
		if (val->fork == -1)
			return (ft_error("fork fail\n"));
		if (val->fork == 0 && val->tmp->full_cmd[0])
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(val->tmp->out_file, 1);
			if (val->tmp->in_file != 0)
				dup2(val->tmp->in_file, 0);
			else
				dup2(val->pe[val->n_p][0], 0);
			ecx(val, get_path(val->env, "PATH"));
		}
	}
	wait_procces();
	if (val->j == 0)
		g_exit_status = 0;
	else
		g_exit_status = 1;
	return (close(val->pe[val->n_p][0]), 0);
}

int	other_commands(t_exec *val)
{
	int	j;

	while (val->tmp->next)
	{
		if (val->tmp->out_file == 1)
			val->tmp->out_file = val->pe[val->n_p + 1][1];
		j = builtins(val);
		if (j == 1 && val->tmp->in_file != -1 && val->tmp->out_file != -1)
		{
			val->fork = fork();
			if (val->fork == -1)
				return (ft_error("fork fail\n"));
			else if (val->fork == 0)
				dup_fd(val);
		}
		else if (j == 0)
			g_exit_status = 0;
		close(val->pe[val->n_p][0]);
		close(val->pe[val->n_p + 1][1]);
		val->tmp = val->tmp->next;
		val->n_p++;
	}
	return (0);
}

int	exc_comande(t_exec *val)
{
	val->pe = (int **)malloc((val->size - 1) * sizeof(int *));
	if (!val->pe)
		return (free(val->pe), 2);
	val->n_p = 0;
	if (init_pipes(val->size - 1, val->pe) == 2)
		return (free(val->pe), 2);
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
