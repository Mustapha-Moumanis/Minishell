/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/06/03 02:49:02 by shilal           ###   ########.fr       */
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

void	init_parssing_data(t_data *data, int ac, char **av)
{
	(void)ac;
	(void)av;
	data->in = 0;
	data->out = 1;
	data->file_error = 0;
}

void	exc_sig(int sig)
{
	sig = 0;
	wait(&sig);
	if (WEXITSTATUS(sig) == 99)
		ft_putchar_fd('\n', 1);
	else
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_exec	val;

	data = (t_data){0};
	ft_lenked_list(env, &val);
	ft_add_shlvl(&val);
	g_exit_status = 0;
	signal(SIGQUIT, SIG_IGN);
	while (1337)
	{
		signal(SIGINT, exc_sig);
		init_parssing_data(&data, ac, av);
		data.n_env = val.env;
		data.error = 0;
		parser(&data, &val);
		if (data.error == 0)
			exuct(&data, &val);
		else if (data.error == 1)
			g_exit_status = 258;
		else if (data.error == 2)
			g_exit_status = 1;
		ft_close(&data.head);
		ft_cmd_clear(&data.head, &ft_double_free);
		ft_lstclear(&data.cmd_lst, &free);
	}
}
