/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:22:03 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/21 16:33:07 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	get_whitespace(t_lexer *lexer, t_token *token, char c)
{
	token->value = malloc(2);
	token->value[0] = c;
	token->value[1] = '\0';
	token->type = WHITE_SPACE;
	token->len = 1;
	lexer->position += 1;
}

void	get_pip(t_lexer *lexer, t_token *token)
{
	token->type = PIPE_LINE;
	if (lexer->input[lexer->position + 1] == '|')
	{
		token->value = ft_strdup("||");
		token->type = OR;
		lexer->position += 1;
	}
	else
		token->value = ft_strdup("|");
	token->len = ft_strlen(token->value);
	lexer->position += 1;
}

void	get_infile_herdok(t_lexer *lexer, t_token *token)
{
	token->type = '<';
	if (lexer->input[lexer->position + 1] == '<')
	{
		token->value = ft_strdup("<<");
		token->type = HERE_DOC;
		lexer->position += 1;
	}
	else
		token->value = ft_strdup("<");
	token->len = ft_strlen(token->value);
	lexer->position += 1;
}

void	get_outfile_append(t_lexer *lexer, t_token *token)
{
	token->type = '>';
	if (lexer->input[lexer->position + 1] == '>')
	{
		token->value = ft_strdup(">>");
		token->type = DREDIR_OUT;
		lexer->position += 1;
	}
	else
		token->value = ft_strdup(">");
	token->len = ft_strlen(token->value);
	lexer->position += 1;
}
