/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/04/07 00:41:17 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	t_data data;
	data = (t_data){0};
	while (1337)
	{
		parser(&data);
		exuct(&data);
		// system("leaks minishell");
	}
}
