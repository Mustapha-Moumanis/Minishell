/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:42:51 by shilal            #+#    #+#             */
/*   Updated: 2023/06/04 18:24:01 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	parent_dir(t_exec *val)
{
	char	*s;

	s = "error retrieving current directory: getcwd: ";
	change_path(val, "OLDPWD", val->last_path);
	add_new_path(val);
	decrement_path(val);
	change_path(val, "PWD", val->last_path);
	if (chdir(val->old_path) == 0)
		return (getcwd(val->old_path, 1024), 0);
	if (val->pos_path == 0)
	{
		val->pos_path += 1;
		return (cd_error(val->tmp->full_cmd[val->i], NULL));
	}
	return (cd_error("cannot access parent directories", s));
}

void	path(t_exec *val)
{
	val->pos_path = 0;
	change_path(val, "OLDPWD", val->cd_path);
	getcwd(val->last_path, 1024);
	getcwd(val->old_path, 1024);
	change_path(val, "PWD", val->last_path);
}

int	check_home(t_exec *val, char *str)
{
	char	*home;

	home = get_path(val->env, "HOME");
	getcwd(val->cd_path, 1024);
	if (!str || !ft_strcmp(str, "~"))
	{
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (2);
		}
		if (chdir(home) == -1)
			return (cd_error(home, NULL));
		path(val);
		return (3);
	}
	return (0);
}

int	cd(t_exec *val)
{
	val->j = check_home(val, val->tmp->full_cmd[val->i]);
	if (val->j != 0)
		return (val->j);
	if (getcwd(val->cd_path, 1024))
	{
		if (chdir(val->tmp->full_cmd[val->i]) == -1)
			return (cd_error(val->tmp->full_cmd[val->i], NULL));
		else
			path(val);
	}
	else if (chdir(val->old_path) == 0)
	{
		change_path(val, "OLDPWD", val->last_path);
		ft_bzero(val->last_path, sizeof(val->last_path));
		getcwd(val->last_path, 1024);
	}
	else
		return (parent_dir(val));
	return (0);
}
