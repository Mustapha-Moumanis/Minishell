/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/04/04 23:19:45 by mmoumani         ###   ########.fr       */
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
		lexer_parsing(&data);
		exuct(&data);
	}
}
