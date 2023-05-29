/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:41:07 by shilal            #+#    #+#             */
/*   Updated: 2023/05/29 13:50:49 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export_env_add(t_exec *val, t_exprt *tmp, char *n, char *v)
{
	t_env		*t_env;

	t_env = val->env;
	while (tmp || t_env)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = v;
			tmp->sep = '\"';
			if (!t_env)
				add_env(&val->env, new_env(n, v));
			else
				add_value_env(val, n, v);
			return ;
		}
		tmp = tmp->next;
		if (t_env)
			t_env = t_env->next;
	}
	add_env(&val->env, new_env(n, v));
	add_export(&val->export, new_export(n, v, '\"'));
}

void	add_value(t_exec *val, char *n)
{
	char		*v;
	t_exprt		*tmp;

	tmp = val->export;
	v = value(val->tmp->full_cmd[val->i]);
	export_env_add(val, tmp, n, v);
}

int	more_value(t_exec *val, char *n)
{
	t_exprt		*tmp;
	t_env		*env;
	char		*str;
	char		*v;

	tmp = val->export;
	env = val->env;
	while (tmp && env)
	{
		if (ft_strcmp(tmp->name, n) == 0)
		{
			v = value(val->tmp->full_cmd[val->i]);
			str = ft_strjoin(tmp->value, v);
			free(v);
			free(tmp->value);
			add_value_env(val, n, str);
			tmp->value = str;
			return (1);
		}
		tmp = tmp->next;
		env = env->next;
	}
	return (0);
}

int	export_(t_exec *val)
{
	char	*n;
	char	*trim;

	n = name(val->tmp->full_cmd[val->i]);
	if (!all_iscorect(val, n))
	{
		g_exit_status = 1;
		return (0);
	}
	else if (ft_strchr(val->tmp->full_cmd[val->i], '='))
	{
		if (n[ft_strlen(n) - 1] == '+')
		{
			trim = ft_strtrim(n, "+");
			free(n);
			if (!more_value(val, trim))
				add_value(val, trim);
		}
		else
			add_value(val, n);
	}
	else
		ft_check_add(val, n);
	return (0);
}

void	export(t_exec *val)
{
	int		j;

	val->i++;
	j = -1;
	if (!val->tmp->full_cmd[val->i])
		print_export(val);
	if (val->size == 1 && val->tmp->in_file >= 0)
	{
		if (val->tmp->full_cmd[val->i])
		{
			while (val->tmp->full_cmd[val->i])
			{
				export_(val);
				val->i++;
			}
		}
		ft_double_free(val->n_env);
		val->n_env = list_to_table_h(&val->env);
	}
}
