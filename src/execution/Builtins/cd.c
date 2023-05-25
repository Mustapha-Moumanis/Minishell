/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:42:51 by shilal            #+#    #+#             */
/*   Updated: 2023/05/25 16:37:59 by shilal           ###   ########.fr       */
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

int	parent_dir(t_exec *val)
{
	char	*s;

	s = "error retrieving current directory: getcwd: ";
	change_path(val, "OLDPWD", val->last_path);
	add_new_path(val);
	decrement_path(val);
	change_path(val, "PWD", val->last_path);
	if (val->pos_path == 0)
	{
		val->pos_path += 1;
		return (cd_error(val->tmp->full_cmd[val->i], NULL));
	}
	return (cd_error("cannot access parent directories", s));
}

int	check_home(t_exec *val, char *str)
{
	char	*home;

	home = get_path(val->env, "HOME");
	if (!str || !ft_strcmp(str, "~"))
	{
		if (chdir(home) == -1)
			return (cd_error(home, NULL));
		return (1);
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
		{
			change_path(val, "OLDPWD", val->cd_path);
			getcwd(val->last_path, 1024);
			getcwd(val->old_path, 1024);
			change_path(val, "PWD", val->last_path);
		}
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
