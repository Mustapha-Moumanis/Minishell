/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:56:13 by shilal            #+#    #+#             */
/*   Updated: 2023/06/01 17:47:01 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lenked_list(char **env, t_exec *val)
{
	char	*n;
	char	*v;
	int		i;

	i = -1;
	val->env = NULL;
	val->export = NULL;
	while (env[++i])
	{
		n = name(env[i]);
		v = value(env[i]);
		add_env(&val->env, new_env(n, v));
		add_export(&val->export, new_export(n, v, '\"'));
	}
	val->n_env = list_to_table_h(&val->env);
}

void	wait_procces(int pid)
{
	int	st;
	int	i;

	i = 0;
	waitpid(pid, &st, 0);
	if (WEXITSTATUS(st))
		g_exit_status = WEXITSTATUS(st);
	if (WIFSIGNALED(st))
		g_exit_status = st + 128;
	if (g_exit_status == 131)
		printf("Quit: 3\n");
	while (wait(&st) > i)
		i = 0;
}

void	ft_close(t_cmd **val)
{
	t_cmd	*tmp;

	tmp = *val;
	while (tmp)
	{
		if (tmp->in_file > 2)
			close(tmp->in_file);
		if (tmp->out_file > 2)
			close(tmp->out_file);
		tmp = tmp->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	str_lowercase(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
}
