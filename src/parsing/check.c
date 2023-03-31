/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:53:20 by shilal            #+#    #+#             */
/*   Updated: 2023/03/31 02:04:51 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check(char *str)
{
	char	**s;

	if (!str)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(str) > 0)
		add_history(str);

	s = ft_split(str, ' ');
	rl_on_new_line();
	return (0); 
}