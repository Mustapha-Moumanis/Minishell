/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:34:26 by shilal            #+#    #+#             */
/*   Updated: 2023/05/08 08:58:05 by shilal           ###   ########.fr       */
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


void	comand_pipe(t_data *data, t_exec *val, int size, int pe[])
{
	dup2(pe[1], data->head->in_file);
	builtins(val, data);
	// if (size == 1)
	// {
	// 	close(pe[1]);
	// 	dup2(pe[0], data->head->out_file);
	// }
	//comand_pipe(data, val, size - 1);
	exit (1);
    printf("%d\n", size);
}