/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:12:30 by shilal            #+#    #+#             */
/*   Updated: 2023/06/01 17:46:47 by mmoumani         ###   ########.fr       */
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

int	unset_error(char *str)
{
	ft_putstr_fd("bash: unset: ", 2);
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
	g_exit_status = 1;
	if (!ft_strcmp("fork fail\n", str) || !ft_strcmp("pipe fail\n", str))
		exit(g_exit_status);
	return (2);
}

void	exc_child_sig(int sig)
{
	(void)sig;
	exit(99);
}
