/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:53:20 by shilal            #+#    #+#             */
/*   Updated: 2023/03/27 14:23:56 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char *str)
{
	char	**s;
	char	*env;

	s = ft_split(str, ' ');
	env = getenv("");
	printf("%s\n", env);
	printf("%s\n", str);
	rl_replace_line(void);
	add_history(str);
	rl_on_new_line();
	return (0);
}