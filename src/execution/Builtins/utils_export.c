/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:59:36 by shilal            #+#    #+#             */
/*   Updated: 2023/05/06 00:00:32 by shilal           ###   ########.fr       */
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

void	export_error(char *str)
{
	ft_putstr_fd("bash: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}
