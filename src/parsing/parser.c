/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:37:26 by shilal            #+#    #+#             */
/*   Updated: 2023/05/20 14:42:28 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_data *data)
{
	data->input = readline("minishell : ");
	if (!data->input)
	{
		rl_clear_history();
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(data->input) > 0)
		add_history(data->input);
	lexer(data);
	syntax_errors(data);
	if (data->error == 0)
		parsing(data, data->elem);
	ft_clear_elems(&data->elem, &free);
	free(data->input);
	return (data->error);
}
