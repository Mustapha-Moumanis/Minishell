/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:53:20 by shilal            #+#    #+#             */
/*   Updated: 2023/03/31 00:07:25 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check(char *str)
{
	char	**s;
	// char	*env;

	if (!str)
	{
		printf("exit\n");
		exit(0);
	}
	s = ft_split(str, ' ');
	// env = getenv("PATH");
	// printf("%s\n", env);

	if (ft_strlen(str) > 0)
		add_history(str);
	// rl_replace_line("\n", 0);
	rl_on_new_line();
	return (0);
}