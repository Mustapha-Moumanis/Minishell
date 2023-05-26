/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:32:50 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/26 18:44:07 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_error(t_list *list)
{
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
}

void	save_error(t_data *data, char *val, int nb)
{
	char	*e1;
	char	*e2;
	char	*tmp;

	if (nb == 1)
	{
		e1 = "Error : ambiguous redirect";
		ft_lstadd_back(&data->save_error, ft_lstnew(ft_strdup(e1)));
	}
	else
	{
		tmp = ft_strdup(val);
		e2 = ft_strjoin(tmp, " : ");
		free(tmp);
		tmp = e2;
		e2 = ft_strjoin(tmp, strerror(errno));
		free(tmp);
		ft_lstadd_back(&data->save_error, ft_lstnew(ft_strdup(e2)));
		free(e2);
	}
	data->file_error = 1;
}

void	in_file(t_data *data, char *value)
{
	if (data->in != -1)
	{
		if (value[0] == 0)
		{
			save_error(data, NULL, 1);
			data->in = -1;
		}
		else
		{
			if (data->in > 2)
				close(data->in);
			data->in = open(value, O_RDONLY, 0644);
			if (data->in == -1)
				save_error(data, value, 2);
		}
	}
}

void	out_file(t_data *data, char *value)
{
	if (data->out != -1)
	{
		if (value[0] == 0)
		{
			save_error(data, NULL, 1);
			data->in = -1;
		}
		else
		{
			if (data->out > 2)
				close(data->out);
			data->out = open(value, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->out == -1)
				save_error(data, value, 2);
		}
	}
}

void	dout_file(t_data *data, char *value)
{
	if (data->out != -1)
	{
		if (value[0] == 0)
		{
			save_error(data, NULL, 1);
			data->in = -1;
		}
		else
		{
			if (data->out > 2)
				close(data->out);
			data->out = open(value, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (data->out == -1)
				save_error(data, value, 2);
		}
	}
}
