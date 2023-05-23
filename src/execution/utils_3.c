/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 08:32:59 by shilal            #+#    #+#             */
/*   Updated: 2023/05/23 11:01:51 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ecx(t_exec *val, char *path)
{
	char	*str;
	int		i;
	char	**s;
	char	*cmd;

	i = 0;
	s = ft_split(path, ':');
	cmd = ft_strjoin("/", val->tmp->full_cmd[0]);
	while (s[i])
	{
		str = ft_strjoin(s[i], cmd);
		if (access(str, R_OK) == 0)
			break ;
		free(str);
		i++;
	}
	ft_double_free(s);
	free(cmd);
	if (!s[i] || val->tmp->full_cmd[0][0] == '\0')
	{
		ft_putstr_fd(val->tmp->full_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(1);
		return (2);
	}
	execve(str, val->tmp->full_cmd, val->n_env);
	ft_putendl_fd(strerror(errno), 2);
	exit(1);
	return (0);
}
