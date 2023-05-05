/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:41:07 by shilal            #+#    #+#             */
/*   Updated: 2023/05/05 20:49:25 by shilal           ###   ########.fr       */
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

void	change_value(t_exec *val, t_data *data, char *n)
{
	t_export	*tmp;

	tmp = val->export;
	while (tmp)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = value(data->head->full_cmd[val->i]);
			free(n);
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

void	add_value(t_exec *val, t_data *data, char *n)
{
	char	*v;

	if (is_cherche(n, val))
		change_value(val, data, n);
	else
	{
		v = value(data->head->full_cmd[val->i]);
		add_env(&val->env, new_env(n, v));
		add_export(&val->export, new_export(n, v, '\"'));
	}
}

void	more_value(t_exec *val, t_data *data, char *n)
{
	t_export	*tmp;
	char 		*str;
	char 		*str2;
	int 		i;

	tmp = val->export;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			str2 = value(data->head->full_cmd[val->i]);
			str = ft_strjoin(tmp->value, str2);
			free(tmp->value);
			tmp->value = str;
			free(str2);
			free(n);
			i = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		add_value(val, data, n);
}

int	all_iscorect(char *str)
{
	int	j;

	j = -1;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[++j])
	{
		if (!ft_isalnum(str[j]) && (str[j] == '+' && str[j + 1]))
			return (0);
	}
	return (1);
}

void	export(t_exec *val, t_data *data)
{
	int		j;
	char 	*n;

	val->i++;
	j = -1;
	if (!data->head->full_cmd[val->i])
		print_export(val, data);
	else
	{
		while (data->head->full_cmd[val->i])
		{
			n = name(data->head->full_cmd[val->i]);
			if (!all_iscorect(n))
			{
				ft_putstr_fd("bash: export: ", 2);
				ft_putstr_fd(data->head->full_cmd[val->i], 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
				free(n);
				break ;
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
			val->i++;
		}
	}
}
