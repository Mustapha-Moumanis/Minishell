/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:53:20 by shilal            #+#    #+#             */
/*   Updated: 2023/04/04 22:17:08 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_quote(t_data *data)
{
	int i;

	i = 0;
	// GONNA CHANGED after check $variables
	while (data->input[i])
	{
		if (data->input[i] == '\"')
			data->d_quote += 1;
		else if (data->input[i] == '\'')
			data->s_quote += 1;
		i++;
	}
	// -------------
	if (data->d_quote % 2 == 1 || data->s_quote % 2 == 1)
	{
		data->d_quote = 0;
		data->s_quote = 0;
		return (0);
	}
	return (1);
}

void	ft_double_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}


int	check(t_data *data)
{
	if (check_quote(data) == 0)
	{
		printf("Quote not closed !!\n");
		return (0);
	}
	rl_on_new_line();
	return (1); 
}