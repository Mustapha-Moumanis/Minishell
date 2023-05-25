/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 08:32:59 by shilal            #+#    #+#             */
/*   Updated: 2023/05/25 19:36:48 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_fd(t_exec *val)
{
	if (val->tmp->in_file != 0)
		dup2(val->tmp->in_file, 0);
	else
		dup2(val->pe[val->n_p][0], 0);
	if (val->tmp->out_file != 1)
		dup2(val->pe[val->n_p + 1][1], 1);
}

void	wait_procces(void)
{
	int	st;

	while (wait(&st) > 0)
	{
		if (WEXITSTATUS(st))
			exit_status = WEXITSTATUS(st);
	}
}

char	*get_path(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, str))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*check_cmd(t_exec *val, char *path)
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
		return (NULL);
	}
	return (str);
}

void	ecx(t_exec *val, char *path)
{
	char	*str;

	if (access(val->tmp->full_cmd[val->i], R_OK) == 0)
		str = val->tmp->full_cmd[val->i];
	else
		str = check_cmd(val, path);
	if (!str)
		exit (127);
	else
	{
		execve(str, val->tmp->full_cmd, val->n_env);
		ft_putendl_fd(strerror(errno), 2);
		exit(128);
	}
}
