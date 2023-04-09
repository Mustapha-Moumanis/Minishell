/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/04/08 03:07:33 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	t_data data;
	data = (t_data){0};
	data.ac = ac;
	data.av = av;
	data.env = env;
	while (1337)
	{
		parser(&data);
		exuct(&data);
		// system("leaks minishell");
	}
}
