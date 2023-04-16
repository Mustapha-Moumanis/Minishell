/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:26:25 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/15 15:31:42 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// <file1 ls -la | wc -l > file2

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

void	lexer_init(t_lexer *lexer, char *input)
{
	*lexer = (t_lexer){0};
	lexer->input = input;
	// lexer->position = 0;
	// lexer->in_file = 0;
	// lexer->error = 0;
}

void	token_init(t_token *token)
{
	*token = (t_token){0};
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (ft_whitespace(lexer->input[lexer->position]))
		lexer->position++;
}

void	lexer_check_token(t_lexer* lexer, t_token *token)
{
	char	c_char;

	lexer_skip_whitespace(lexer);
	c_char = lexer->input[lexer->position];
	if (c_char == '\"' || c_char == '\'')
	{
		lexer->position++;
		lexer_read_cmd_quote(lexer, token);
	}
	else
		lexer_read_cmd(lexer, token);		
}

void	lexer_append(t_lexer *lexer, t_token *token)
{
	lexer->position += 2;
	lexer_check_token(lexer, token);
	if (token->type != TOKEN_END)
		token->type = TOKEN_APPEND;
}

void	lexer_out_file(t_lexer *lexer, t_token *token)
{
	lexer->position += 1;

	lexer_check_token(lexer, token);
	if (token->type != TOKEN_END)
		token->type = TOKEN_OUT_FILE;
}

void	lexer_heredoc(t_lexer *lexer, t_token *token)
{
	lexer->position += 2;
	lexer_check_token(lexer, token);
	if (token->type != TOKEN_END)
		token->type = TOKEN_HD;
}

void	lexer_in_file(t_lexer *lexer, t_token *token)
{
	lexer->position += 1;
	lexer_check_token(lexer, token);
	if (token->type != TOKEN_END)
		token->type = TOKEN_IN_FILE;
}

void	lexer_next_lexer(t_lexer *lexer, t_token *token)
{
	char	c_char;

	lexer_skip_whitespace(lexer);
	c_char = lexer->input[lexer->position];
	if (c_char == '>')
	{
		if (lexer->input[lexer->position + 1] == '>')
			lexer_append(lexer, token);
		else
			lexer_out_file(lexer, token);
	}
	else if (c_char == '<')
	{
		if (lexer->input[lexer->position + 1] == '<')
			lexer_heredoc(lexer, token);
		else
			lexer_in_file(lexer, token);
	}
	else if (c_char == '|')
	{
		lexer->position++;
		token->value = "|";
		token->type = TOKEN_PIPE;
	}
	else if (c_char == '\0' || c_char == '\n')
	{
		token->type = TOKEN_END;
		token->value = "";
	}
	else
		lexer_check_token(lexer, token);
}

void check_in_file(t_data *data, t_lexer *lexer, t_token *token)
{
	if (data->in > 2)
		close(data->in);
	data->in = open(token->value, O_RDONLY);
	if (data->in == -1)
	{
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
		ft_putstr_fd(" : outfile\n", 2);
		lexer->error = 1;
		token->type = TOKEN_END;
	}
}

void	check_token(t_data *data, t_lexer *lexer, t_token *token)
{	
	if (token->type == TOKEN_OUT_FILE)
	{
		check_out_file(data, lexer, token);
		// printf("TOKEN_OUT_FILE %s\n", token->value);
	}
	// if (token->type == TOKEN_HD)
		// printf("TOKEN_HD %s\n", token->value);
	if (token->type == TOKEN_IN_FILE)
	{
		// printf("TOKEN_IN_FILE %s\n", token->value);
		check_in_file(data, lexer, token);
	}
	if (token->type == TOKEN_COMMAND)
	{
		// printf("TOKEN_COMMAND %s\n", token->value);
		ft_lstadd_back(&data->cmd_lst, ft_lstnew(ft_strdup(token->value)));
	}
	// if (token->type == TOKEN_APPEND)
		// printf("TOKEN_APPEND %s\n", token->value);
	if (token->type == TOKEN_PIPE)
	{
		append_exution_struct(data);
		// printf("TOKEN_PIPE %s\n", token->value);
	}
	if (token->type == TOKEN_END)
	{
		append_exution_struct(data);
		// printf("TOKEN_END\n");
	}
}

void	lexer(t_data *data)
{
	t_lexer	lexer;
	t_token	token;

	lexer_init(&lexer, data->input);
	token_init(&token);
	while (token.type != TOKEN_END)
	{
		lexer_next_lexer(&lexer, &token);
		check_token(data, &lexer, &token);
		if (lexer.error == 1)
			data->error = 1;
	}
}
// 