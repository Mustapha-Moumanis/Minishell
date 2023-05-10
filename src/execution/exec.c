/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:34:26 by shilal            #+#    #+#             */
/*   Updated: 2023/05/10 05:10:31 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ecx(char **av, char **en)
{
	char	*str;
	int		i;
	char	*env;
	char	**s;
	char	*cmd;

	i = 0;
	env = getenv("PATH");
	s = ft_split(env, ':');
	cmd = ft_strjoin("/", av[0]);
	while (s[i])
	{
		str = ft_strjoin(s[i], cmd);
		if (access(str, R_OK) == 0)
			break ;
		i++;
	}
	execve(str, av, en);
	perror("error");
}


int	ft_lstsize_h(t_cmd *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	init_pipes(int size, int **pe)
{
	int	i;

	i = -1;
	pe = (int **)malloc(size * sizeof(int *));
	while (++i < size)
		pe[i] = (int *)malloc(2 * sizeof(int));
	i = -1;
	while (++i < size)
		pipe(pe[i]);
}

// --fonction for generate the pipes-- //

void	ecxute_command(t_data *data, t_exec *val)
{
	int	**pe;
	int	fr;
	int	i;

	i = val->size;
	init_pipes(val->size, pe);
	while (data->head)
	{
		fr = fork();
		if (fr == 0)
		{
			if (val->size == 0)
				builtins(val, data);
			close(pe[val->size - i][0]);
			dup2(pe[val->size - i][1], data->head->out_file);
			builtins(val, data);
		}
		waitpid(fr, NULL, 0);
		data->head = data->head->next;
		i--;
	}
	ft_close_all(pe);
	waitpid(fr, NULL, 0);
}