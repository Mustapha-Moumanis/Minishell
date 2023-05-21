/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:26:25 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/21 12:02:39 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_quote(int c)
{
	return (c == '\"' || c == '\'');
}

int	is_red(int c)
{
	return (c == '>' || c == '<' || c == HERE_DOC || c == DREDIR_OUT);
}

int	special_char(char c)
{
	return (ft_quote(c) || is_red(c) || c == '|' || c == '$' || c == '\\');
}

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

char	*cat_var(char *str, int nb)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	if (nb)
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	else
		while (str[i] && !special_char(str[i]) && !ft_whitespace(str[i]))
			i++;
	value = malloc(sizeof(char) * (i + 1));
	if (!value)
		return (NULL);
	j = -1;
	while (++j < i)
		value[j] = str[j];
	value[j] = '\0';
	return (value);
}

void	get_word(t_lexer *lexer, t_token *token)
{
	char	*value;

	value = cat_var(lexer->input + lexer->position, 0);
	lexer->position += ft_strlen(value);
	token->value = value;
	token->len = ft_strlen(token->value);
	token->type = WORD;
}

void	get_env(t_lexer *lexer, t_token *token)
{
	char	*str;
	char	c_char;
	char	*value;

	c_char = lexer->input[lexer->position];
	str = cat_var(lexer->input + lexer->position + 1, 1);
	value = ft_strjoin("$", str);
	if (lexer->input[lexer->position + 1] == '$')
	{
		free(value);
		value = ft_strdup("$$");
		token->type = WORD;
	}
	else if (lexer->input[lexer->position + 1] == '?')
	{
		free(value);
		value = ft_strdup("$?");
		token->type = EXIT_STATUS;
	}
	else
		token->type = c_char;
	token->value = value;
	lexer->position += ft_strlen(value);
	free(str);
}

int	initial_token(t_token *token, char c)
{
	token->value = malloc(2);
	token->value[0] = c;
	token->value[1] = '\0';
	token->len = 1;
	token->type = c;
	return (1);
}

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
	else if (c == '$')
		get_env(lexer, token);
	else if (c == '<')
		get_infile_herdok(lexer, token);
	else if (c == '>')
		get_outfile_append(lexer, token);
}

enum e_state change_state(enum e_state	state, enum e_type type)
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
		if (state == IN_QUOTE && t.type == ENV)
			t.type = WORD;
		if ((state == IN_QUOTE && t.type == QOUTE)
			|| (state == IN_DQUOTE && t.type == DQUOTE))
			addback_elem(&d->elem, new_elem(t.value, t.len, t.type, GENERAL));
		else
			addback_elem(&d->elem, new_elem(t.value, t.len, t.type, state));
	}
}
