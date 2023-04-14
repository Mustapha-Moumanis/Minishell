/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:41:07 by shilal            #+#    #+#             */
/*   Updated: 2023/04/14 07:01:24 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	sort_env(t_data *data)
{
	int	i;
	int	v;

	i = 0;
	v = 'A';
	while (data->env[i][0] != v)
		i++;
	ft_putstr_fd(data->env[i], 1);
}

void	print_export(t_data *data, t_exec *val)
{
	(void)val;
	ft_putstr_fd("declare -x ", 1);
	sort_env(data);
	ft_putchar_fd('\n', 1);
}

void	export(t_exec *val, t_data *data)
{
	val->i++;
	if (!data->head->full_cmd[val->i])
	{
		print_export(data, val);
	}
}
