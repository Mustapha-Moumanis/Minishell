/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:59:36 by shilal            #+#    #+#             */
/*   Updated: 2023/05/23 10:58:50 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_export(t_exec *val)
{
	t_exprt	*tmp;

	tmp = val->export;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", val->tmp->out_file);
		ft_putstr_fd(tmp->name, val->tmp->out_file);
		if (tmp->value)
		{
			ft_putchar_fd('=', val->tmp->out_file);
			ft_putchar_fd(tmp->sep, val->tmp->out_file);
			ft_putstr_fd(tmp->value, val->tmp->out_file);
			ft_putchar_fd(tmp->sep, val->tmp->out_file);
		}
		ft_putstr_fd("\n", val->tmp->out_file);
		tmp = tmp->next;
	}
}

void	export_error(char *str)
{
	ft_putstr_fd("bash: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	add_export(t_exprt **lst, t_exprt *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast_export(*lst)->next = new;
}

void	add_env(t_env **lst, t_env *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast_env(*lst)->next = new;
}

int	add_value_export(t_exec *val, char *n, char *v)
{
	t_env	*tmp;

	tmp = val->env;
	while (tmp)
	{
		if (ft_strcmp(n, tmp->name) == 0)
		{
			tmp->value = v;
			free(n);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
