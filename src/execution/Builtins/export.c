/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:41:07 by shilal            #+#    #+#             */
/*   Updated: 2023/05/25 19:27:28 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_value(t_exec *val, char *n)
{
	int			j;
	char		*v;
	t_exprt		*tmp;

	tmp = val->export;
	v = value(val->tmp->full_cmd[val->i]);
	while (tmp)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = v;
			tmp->sep = '\"';
			break ;
		}
		tmp = tmp->next;
	}
	j = add_value_export(val, n, v);
	if (j == 0 && tmp)
		add_env(&val->env, new_env(n, v));
	else
	{
		add_env(&val->env, new_env(n, v));
		add_export(&val->export, new_export(n, v, '\"'));
	}
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
			env->value = str;
			free(tmp->value);
			tmp->value = str;
			free(v);
			free(n);
			return (1);
		}
		tmp = tmp->next;
		env = env->next;
	}
	return (0);
}

int	all_iscorect(t_exec *val, char *str)
{
	int	j;
	int	len;

	j = -1;
	len = ft_strlen(str);
	if (len == 0)
		return (free(str), export_error(val->tmp->full_cmd[val->i]));
	if (ft_isdigit(str[0]))
		return (free(str), export_error(val->tmp->full_cmd[val->i]));
	if (str[len - 1] == '+')
		len -= 1;
	while (++j < len)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (free(str), export_error(val->tmp->full_cmd[val->i]));
	}
	return (1);
}

int	export_(t_exec *val)
{
	char	*n;
	char	*trim;

	n = name(val->tmp->full_cmd[val->i]);
	if (!all_iscorect(val, n))
	{
		exit_status = 1;
		return (0);
	}
	else if (ft_strchr(val->tmp->full_cmd[val->i], '='))
	{
		if (n[ft_strlen(n) - 1] == '+')
		{
			trim = ft_strtrim(n, "+");
			if (!more_value(val, trim))
				add_value(val, trim);
			free(n);
		}
		else
			add_value(val, n);
	}
	else
		add_export(&val->export, new_export(n, NULL, '\0'));
	return (0);
}

void	export(t_exec *val)
{
	int		j;

	val->i++;
	j = -1;
	if (!val->tmp->full_cmd[val->i])
		print_export(val);
	else if (val->tmp->full_cmd[val->i] && !val->tmp->next)
	{
		if (val->tmp->in_file == 0)
		{
			while (val->tmp->full_cmd[val->i])
			{
				export_(val);
				val->i++;
			}
			ft_double_free(val->n_env);
			val->n_env = list_to_table_h(&val->env);
		}
	}
}
