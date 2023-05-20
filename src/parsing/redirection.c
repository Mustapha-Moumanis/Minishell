/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:32:50 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/19 17:11:14 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	in_file(t_data *data, char *value)
{
	if (data->in > 2)
		close(data->in);
	data->in = open(value, O_RDONLY);
	if (data->in == -1)
	{
		ft_putstr_fd(value, 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		data->error = 1;
	}
}

void	out_file(t_data *data, char *value)
{
	if (data->out > 2)
		close(data->out);
	data->out = open(value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->out == -1)
	{
		ft_putstr_fd(value, 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		data->error = 1;
	}
}

void	dout_file(t_data *data, char *value)
{
	if (data->out > 2)
		close(data->out);
	data->out = open(value, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (data->out == -1)
	{
		ft_putstr_fd(value, 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		data->error = 1;
	}
}
