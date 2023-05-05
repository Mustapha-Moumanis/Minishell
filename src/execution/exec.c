/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:34:26 by shilal            #+#    #+#             */
/*   Updated: 2023/05/02 13:57:19 by shilal           ###   ########.fr       */
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
			break;
		i++;
	}
	execve(str, av, en);
}
