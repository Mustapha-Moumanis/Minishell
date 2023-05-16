/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:42:51 by shilal            #+#    #+#             */
/*   Updated: 2023/05/11 06:23:46 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cd_error(char *obt)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(obt, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
}

void	add_new_path(t_exec *val)
{
	int	i;
	int	j;

	j = -1;
	i = ft_strlen(val->last_path);
	val->last_path[i++] = '/';
	while (val->tmp->full_cmd[++j])
		val->last_path[i++] = val->tmp->full_cmd[val->i][j];
}

void	decrement_path(t_exec *val)
{
	int	i;

	i = ft_strlen(val->old_path);
	while (val->old_path[--i])
	{
		if (val->old_path[i] == '/')
			break ;
		val->old_path[i] = '\0';
	}
	val->old_path[i] = '\0';
}

void	parent_dir(t_exec *val)
{
	if (val->pos_path == 0)
	{
		val->pos_path += 1;
		add_new_path(val);
		decrement_path(val);
		cd_error(val->tmp->full_cmd[val->i]);
	}
	else if (val->pos_path != 0)
	{
		val->pos_path += 1;
		add_new_path(val);
		decrement_path(val);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	change_path(val, "OLDPWD", val->cd_path);
	change_path(val, "PWD", val->last_path);
}

void	cd(t_exec *val)
{
	val->i++;
	if (val->tmp->full_cmd[val->i])
	{
		if (getcwd(val->cd_path, 1024))
		{
			if (chdir(val->tmp->full_cmd[val->i]) == -1)
				cd_error(val->tmp->full_cmd[val->i]);
			else
			{
				change_path(val, "OLDPWD", val->cd_path);
				getcwd(val->last_path, 1024);
				getcwd(val->old_path, 1024);
				change_path(val, "PWD", val->last_path);
			}
		}
		else if (chdir(val->old_path) == 0)
		{
			ft_bzero(val->last_path, sizeof(val->last_path));
			getcwd(val->last_path, 1024);
		}
		else
			parent_dir(val);
	}
	else
		chdir(getenv("HOME"));
}
