/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:37:26 by shilal            #+#    #+#             */
/*   Updated: 2023/04/04 18:26:45 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(t_data *data)
{
	data->input = readline("minishell-> ");
	if (!data->input)
	{
		rl_clear_history();
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(data->input) > 0)
		add_history(data->input);
	// data->s = ft_split(data->input, '|');
	check(data);
	// ft_double_free(data->s);
	free(data->input);
}