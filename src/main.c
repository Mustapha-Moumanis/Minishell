/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/05/30 23:04:12 by mmoumani         ###   ########.fr       */
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

	(void)ac;
	(void)av;
	data = (t_data){0};
	ft_lenked_list(env, &val);
	val.pos_path = 0;
	g_exit_status = 0;
	signal(SIGQUIT, SIG_IGN);
	while (1337)
	{
		signal(SIGINT, exc_sig);
		init_parssing_data(&data);
		data.n_env = val.env;
		data.error = 0;
		if (parser(&data) == 0)
			exuct(&data, &val);
		else
			g_exit_status = 258;
		ft_cmd_clear(&data.head, &ft_double_free);
		ft_lstclear(&data.cmd_lst, &free);
	}
}
