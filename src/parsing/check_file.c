/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:58:17 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/03 21:30:29 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_in_file(t_data *data, t_lexer *lexer, t_token *token)
{
	if (data->in > 2)
		close(data->in);
	data->in = open(token->value, O_RDONLY);
	if (data->in == -1)
	{
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd(strerror(errno), 2);
		lexer->error = 1;
		token->type = TOKEN_END;
	}
}

void	check_out_file(t_data *data, t_lexer *lexer, t_token *token)
{
	if (data->out > 2)
		close(data->out);
	data->out = open(token->value, O_CREAT | O_RDWR, 0644);
	if (data->out == -1)
	{
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd(strerror(errno), 2);
		lexer->error = 1;
		token->type = TOKEN_END;
	}
}

void	check_append_file(t_data *data, t_lexer *lexer, t_token *token)
{
	if (data->out > 2)
		close(data->out);
	data->out = open(token->value, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (data->out == -1)
	{
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd(strerror(errno), 2);
		lexer->error = 1;
		token->type = TOKEN_END;
	}
}
