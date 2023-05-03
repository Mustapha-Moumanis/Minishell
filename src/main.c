/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/05/03 21:24:12 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_cmd	cmd;
	t_exec	val;

	(void)ac;
	(void)av;
	data = (t_data){0};
	data.env = env;
	val.pos_path = 0;
	init_parssing_data(&data);
	while (1337)
	{
		data.error = 0;
		if (parser(&data) == 0)
			exuct(&cmd, &data, &val);
		ft_lst_clear(&data.head, &ft_double_free);
		ft_lstclear(&data.cmd_lst, &free);
	}
}
