/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:41:07 by shilal            #+#    #+#             */
/*   Updated: 2023/05/22 17:38:23 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_value(t_exec *val, char *n)
{
	int			j;
	char		*v;
	t_exprt	*tmp;

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

void	more_value(t_exec *val, char *n)
{
	t_exprt	*tmp;
	t_env		*env;
	char		*str;
	char		*v; 

	tmp = val->export;
	env = val->env;
	while (tmp && env)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			v = value(val->tmp->full_cmd[val->i]);
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
		add_value(val, n);
}

int	all_iscorect(char *str)
{
	int	j;

	j = -1;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[++j])
		if (!ft_isalnum(str[j]) && (str[j] == '+' && str[j + 1]))
			return (0);
	return (1);
}

int	export_(t_exec *val)
{
	char	*n;

	n = name(val->tmp->full_cmd[val->i]);
	if (!all_iscorect(n))
	{
		export_error(val->tmp->full_cmd[val->i]);
		free(n);
		return (1);
	}
	else if (ft_strchr(val->tmp->full_cmd[val->i], '='))
	{
		if (n[ft_strlen(n) - 1] == '+')
		{
			more_value(val, ft_strtrim(n, "+"));
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
	else
	{
		while (val->tmp->full_cmd[val->i])
		{
			if (export_(val) == 1)
				break ;
			val->i++;
		}
	}
	ft_double_free(val->n_env);
	val->n_env = list_to_table_h(&val->env);
}
