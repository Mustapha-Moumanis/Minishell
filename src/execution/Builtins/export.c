/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:41:07 by shilal            #+#    #+#             */
/*   Updated: 2023/05/05 16:16:43 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_export(t_exec *val, t_data *data)
{
	t_export	*tmp;

	tmp = val->export;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", data->head->out_file);
		ft_putstr_fd(tmp->name, data->head->out_file);
		if (tmp->value)
		{
			ft_putchar_fd('=', data->head->out_file);
			ft_putchar_fd(tmp->sep, data->head->out_file);
			ft_putstr_fd(tmp->value, data->head->out_file);
			ft_putchar_fd(tmp->sep, data->head->out_file);
		}
		ft_putstr_fd("\n", data->head->out_file);
		tmp = tmp->next;
	}
}

void	more_value(t_exec *val, t_data *data, char *n)
{
	t_export	*tmp;

	tmp = val->export;
	while (tmp)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			tmp->value = ft_strjoin(value(data->head->full_cmd[val->i]), tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	change_value(t_exec *val, t_data *data, char *n)
{
	t_export	*tmp;

	tmp = val->export;
	while (tmp)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			tmp->value = value(data->head->full_cmd[val->i]);
			break ;
		}
		tmp = tmp->next;
	}
}

int	is_cherche(char *str,t_exec *val)
{
	t_export	*tmp;

	tmp = val->export;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	add_value(t_exec *val, t_data *data)
{
	char 	*n;
	char	*v;

	n = name(data->head->full_cmd[val->i]);
	if (n[ft_strlen(n) - 1] == '+')
		more_value(val, data, ft_strtrim(n, "+"));
	else if (is_cherche(n, val))
		change_value(val, data, n);
	else
	{
		if (ft_strchr(data->head->full_cmd[val->i], '='))
		{
			v = value(data->head->full_cmd[val->i]);
			if (!v)
				ft_putendl_fd("error", data->head->out_file);
			add_env(&val->env, new_env(n, v));
			add_export(&val->export, new_export(n, v, '\"'));
		}
		else
			add_export(&val->export, new_export(n, NULL, ' '));
	}
}

void	export(t_exec *val, t_data *data)
{
	val->i++;
	if (!data->head->full_cmd[val->i])
		print_export(val, data);
	else
	{
		while (data->head->full_cmd[val->i])
		{
			add_value(val, data);
			val->i++;
		}
	}
}
