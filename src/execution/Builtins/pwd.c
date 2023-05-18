/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 07:19:55 by shilal            #+#    #+#             */
/*   Updated: 2023/05/18 09:11:56 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_path(t_exec *val, char *str, char *value)
{
	t_export	*tmp;
	t_env		*env;
	char		*s;

	tmp = val->export;
	env = val->env;
	while (tmp && env)
	{
		if (!ft_strcmp(tmp->name, str))
		{
			free(tmp->value);
			s = ft_strdup(value);
			tmp->value = s;
			env->value = s;
			break ;
		}
		tmp = tmp->next;
		env = env->next;
	}
}

void	pwd(t_exec *val)
{
	if (getcwd(val->cd_path, 1024))
	{
		change_path(val, "PWD", val->cd_path);
		ft_putendl_fd(val->cd_path, val->tmp->out_file);
	}
	else
	{
		val->pos_path += 1;
		decrement_path(val);
		ft_putendl_fd(val->last_path, val->tmp->out_file);
	}
}
