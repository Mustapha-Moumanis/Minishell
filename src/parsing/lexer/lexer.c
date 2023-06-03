/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:26:25 by mmoumani          #+#    #+#             */
/*   Updated: 2023/06/03 23:04:42 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	lexer_init(t_lexer *lexer, char *input)
{
	*lexer = (t_lexer){0};
	lexer->input = input;
	lexer->len = ft_strlen(input);
}

void	token_init(t_token *token)
{
	*token = (t_token){0};
	token->value = NULL;
	token->type = WORD;
	token->state = GENERAL;
}

void	lexer_next_token(t_lexer *lexer, t_token *token)
{
	char	c;

	c = lexer->input[lexer->position];
	if (ft_isalnum(c) || (!special_char(c) && !ft_whitespace(c)))
		get_word(lexer, token);
	else if (ft_quote(c) || c == '\\' || c == '\n')
		lexer->position += initial_token(token, c);
	else if (ft_whitespace(c))
		get_whitespace(lexer, token, c);
	else if (c == '|')
		get_pip(lexer, token);
	else if (c == '&')
		get_and(lexer, token);
	else if (c == '$')
		get_env(lexer, token, c, lexer->input[lexer->position + 1]);
	else if (c == '<')
		get_infile_herdok(lexer, token);
	else if (c == '>')
		get_outfile_append(lexer, token);
}

enum e_state	change_state(enum e_state state, enum e_type type)
{
	if (state == GENERAL)
	{
		if (type == QOUTE)
			state = IN_QUOTE;
		else if (type == DQUOTE)
			state = IN_DQUOTE;
	}
	else if (state == IN_QUOTE && type == QOUTE)
		state = GENERAL;
	else if (state == IN_DQUOTE && type == DQUOTE)
		state = GENERAL;
	return (state);
}

void	lexer(t_data *d)
{
	t_lexer			lexer;
	t_token			t;
	enum e_state	state;

	state = GENERAL;
	lexer_init(&lexer, d->input);
	token_init(&t);
	while (lexer.position < lexer.len && lexer.input[lexer.position] != '\0')
	{
		lexer_next_token(&lexer, &t);
		state = change_state(state, t.type);
		if (state == IN_QUOTE && (t.type == ENV || t.type == EXIT_STATUS))
			t.type = WORD;
		if ((state == IN_QUOTE && t.type == QOUTE)
			|| (state == IN_DQUOTE && t.type == DQUOTE))
			addback_elem(&d->elem, new_elem(t.value, t.type, GENERAL));
		else
			addback_elem(&d->elem, new_elem(t.value, t.type, state));
	}
}
