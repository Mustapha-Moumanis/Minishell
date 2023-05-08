/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:41:07 by shilal            #+#    #+#             */
/*   Updated: 2023/05/08 00:32:33 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_value(t_exec *val, t_data *data, char *n)
{
	char		*v;
	t_export	*tmp;
	t_env		*env;

	tmp = val->export;
	env = val->env;
	v = value(data->head->full_cmd[val->i]);
	while (tmp && env)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = v;
			env->value = v;
			free(n);
			break ;
		}
		tmp = tmp->next;
		env = env->next;
	}
	if (!tmp)
	{
		add_env(&val->env, new_env(n, v));
		add_export(&val->export, new_export(n, v, '\"'));
	}
}

void	more_value(t_exec *val, t_data *data, char *n)
{
	t_export	*tmp;
	t_env		*env;
	char		*str;
	char		*v;

	tmp = val->export;
	env = val->env;
	while (tmp && env)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			v = value(data->head->full_cmd[val->i]);
			str = ft_strjoin(tmp->value, v);
			env->value = str;
			free(tmp->value);
			tmp->value = str;
			free(v);
			free(n);
			break ;
		}
		tmp = tmp->next;
		env = env->next;
	}
	if (!tmp)
		add_value(val, data, n);
}

int	all_iscorect(char *str)
{
	int	j;

	j = -1;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[++j])
		if (!ft_isalnum(str[j]) || (str[j] == '+' && str[j + 1]))
			return (0);
	return (1);
}

int	export_(t_exec *val, t_data *data)
{
	char	*n;

	n = name(data->head->full_cmd[val->i]);
	if (!all_iscorect(n))
	{
		export_error(data->head->full_cmd[val->i]);
		free(n);
		return (1);
	}
	else if (ft_strchr(data->head->full_cmd[val->i], '='))
	{
		if (n[ft_strlen(n) - 1] == '+')
		{
			more_value(val, data, ft_strtrim(n, "+"));
			free(n);
		}
		else
			add_value(val, data, n);
	}
	else
		add_export(&val->export, new_export(n, NULL, '\0'));
	return (0);
}

void	export(t_exec *val, t_data *data)
{
	int		j;

	val->i++;
	j = -1;
	if (!data->head->full_cmd[val->i])
		print_export(val, data);
	else
	{
		while (data->head->full_cmd[val->i])
		{
			if (export_(val, data) == 1)
				break ;
			val->i++;
		}
	}
}
