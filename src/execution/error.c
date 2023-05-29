/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:12:30 by shilal            #+#    #+#             */
/*   Updated: 2023/05/29 13:50:49 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_error(char *str)
{
	ft_putstr_fd("bash: export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (0);
}

int	cd_error(char *obt, char *s)
{
	ft_putstr_fd("cd: ", 2);
	if (s)
		ft_putstr_fd(s, 2);
	ft_putstr_fd(obt, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
	return (2);
}

int	ft_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(str, 2);
	return (2);
}

void	wait_procces(void)
{
	int	st;
	int	j;

	g_exit_status = 0;
	j = 1;
	while (j > 0)
	{
		j = wait(&st);
		if (WEXITSTATUS(st))
			g_exit_status = WEXITSTATUS(st);
	}
}
