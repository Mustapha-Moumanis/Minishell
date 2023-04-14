/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:59:00 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/14 07:00:52 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	sp_builtins(t_exec *val, t_data *data)
{
	val->check = data->head->full_cmd[0];
	if (val->check)
	{
		str_lowercase(val->check);
		if (ft_strcmp(val->check, "echo") == 0)
			echo(val, data);
		else if (ft_strcmp(val->check, "pwd") == 0)
			pwd(val);
		else if (ft_strcmp(val->check, "env") == 0)
			env(val, data);
		else
			val->onther = 1;
	}
}

void	builtins(t_exec *val, t_data *data)
{
	if (ft_strcmp(data->head->full_cmd[val->i], "cd") == 0)
		cd(val, data);
	else if (ft_strcmp(data->head->full_cmd[val->i], "export") == 0)
		export(val, data);
	else if (ft_strcmp(data->head->full_cmd[val->i], "unset") == 0)
		echo(val, data);
	else if (ft_strcmp(data->head->full_cmd[val->i], "exit") == 0)
		echo(val, data);
	else
		sp_builtins(val, data);
}

void	exuct(t_cmd *cmd, t_data *data, t_exec *val)
{
	(void)cmd;
	val->onther = 0;
	val->i = 0;
	builtins(val, data);
	if (val->onther == 1)
		printf("Onther command\n");
}
