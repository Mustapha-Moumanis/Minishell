/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:21:11 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/31 19:40:26 by mmoumani         ###   ########.fr       */
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
	syntax_errors(data, data->elem);
	if (data->error == 0)
		parsing(data, data->elem);
	ft_clear_elems(&data->elem, &free);
	free(data->input);
	return (data->error);
}
