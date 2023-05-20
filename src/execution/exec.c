/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:34:26 by shilal            #+#    #+#             */
/*   Updated: 2023/05/20 15:09:08 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ecx(t_exec *val, char *path)
{
	char	*str;
	int		i;
	char	**s;
	char	*cmd;

	i = 0;
	s = ft_split(path, ':');
	cmd = ft_strjoin("/", val->tmp->full_cmd[0]);
	while (s[i])
	{
		str = ft_strjoin(s[i], cmd);
		if (access(str, R_OK) == 0)
			break ;
		free(str);
		i++;
	}
	ft_double_free(s);
	free(cmd);
	execve(str, val->tmp->full_cmd, val->n_env);
	perror("Error");
	exit(1);
	return (0);
}

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
		waitpid(val->fork, NULL, 0);
	}
	close(val->pe[val->n_p][1]);
	val->tmp = val->tmp->next;
	return (0);
}

int	last_cmd(t_exec *val)
{
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
		waitpid(val->fork, NULL, 0);
	}
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
			waitpid(val->fork, NULL, 0);
		}
		close(val->pe[val->n_p][0]);
		close(val->pe[val->n_p + 1][1]);
		val->tmp = val->tmp->next;
		val->n_p++;
	}
	return (0);
}

int	ft_free_pipes(int **pipe, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(pipe[i++]);
	}
	free(pipe);
	return (2);
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
		first_cmd(val);
		other_commands(val);
		last_cmd(val);
		ft_free_pipes(val->pe, val->size - 1);
	}
	return (0);
}
