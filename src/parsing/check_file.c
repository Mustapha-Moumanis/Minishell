/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:58:17 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/16 20:43:45 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void check_in_file(t_data *data, t_lexer *lexer, t_token *token)
{
	if (data->in > 2)
		close(data->in);
	data->in = open(token->value, O_RDONLY);
	if (data->in == -1)
	{
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd(strerror(data->in), 2);
		lexer->error = 1;
		token->type = TOKEN_END;
	}
}

void check_out_file(t_data *data, t_lexer *lexer, t_token *token)
{
	if (data->out > 2)
		close(data->out);
	data->out = open(token->value, O_CREAT, 0644);
	if (data->out == -1)
	{
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd(strerror(data->out), 2);
		lexer->error = 1;
		token->type = TOKEN_END;
	}
}

void check_append_file(t_data *data, t_lexer *lexer, t_token *token)
{
    if (data->out > 2)
		close(data->out);
	data->out = open(token->value, O_CREAT | O_APPEND, 0644);
	if (data->out == -1)
	{
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd(strerror(data->out), 2);
		lexer->error = 1;
		token->type = TOKEN_END;
	}
}
