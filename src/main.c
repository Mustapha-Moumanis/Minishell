/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/05/23 11:46:31 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(str, 2);
	return (2);
}

void	ft_double_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	init_parssing_data(t_data *data)
{
	data->in = 0;
	data->out = 1;
	data->file_error = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_exec	val;

	(void)ac;
	(void)av;
	data = (t_data){0};
	data.env = env;
	val.pos_path = 0;
	ft_lenked_list(data.env, &val);
	data.n_env = val.env;
	while (1337)
	{
		init_parssing_data(&data);
		data.error = 0;
		if (parser(&data) == 0)
			exuct(&data, &val);
		ft_cmd_clear(&data.head, &ft_double_free);
		ft_lstclear(&data.cmd_lst, &free);
	}
}
