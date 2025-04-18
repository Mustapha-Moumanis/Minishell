/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/06/03 20:23:03 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_status = 0;

void	ft_add_shlvl(t_exec *val)
{
	t_exprt	*tmp;
	char	*str;
	t_env	*env;
	int		j;

	tmp = val->export;
	env = val->env;
	while (tmp && env)
	{
		if (!ft_strcmp(tmp->name, "SHLVL"))
		{
			j = ft_atoi(tmp->value) + 1;
			free(tmp->value);
			str = ft_itoa(j);
			tmp->value = str;
			env->value = str;
			break ;
		}
		tmp = tmp->next;
		env = env->next;
	}
	ft_double_free(val->n_env);
	val->n_env = list_to_table_h(&val->env);
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
