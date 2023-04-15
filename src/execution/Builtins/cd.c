/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:42:51 by shilal            #+#    #+#             */
/*   Updated: 2023/04/15 14:24:58 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cd_error(char *obt)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(obt, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
}

void	add_new_path(t_exec *val, t_data *data)
{
	int	i;
	int	j;

	j = -1;
	i = ft_strlen(val->last_path);
	val->last_path[i++] = '/';
	while (data->head->full_cmd[++j])
		val->last_path[i++] = data->head->full_cmd[val->i][j];
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

void	parent_dir(t_exec *val, t_data *data)
{
	if (val->pos_path == 0)
	{
		val->pos_path += 1;
		add_new_path(val, data);
		decrement_path(val);
		cd_error(data->head->full_cmd[val->i]);
	}
	else if (val->pos_path != 0)
	{
		add_new_path(val, data);
		decrement_path(val);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
}

void	cd(t_exec *val, t_data *data)
{
	val->i++;
	if (data->head->full_cmd[val->i])
	{
		if (getcwd(val->cd_path, 1024))
		{
			if (chdir(data->head->full_cmd[val->i]) == -1)
				cd_error(data->head->full_cmd[val->i]);
			else
			{
				getcwd(val->last_path, 1024);
				getcwd(val->old_path, 1024);
			}
		}
		else if (chdir(val->old_path) == 0)
		{
			ft_bzero(val->last_path, sizeof(val->last_path));
			getcwd(val->last_path, 1024);
		}
		else
			parent_dir(val, data);
	}
	else
		chdir(getenv("HOME"));
}
