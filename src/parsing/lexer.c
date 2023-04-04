/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:39:17 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/04 23:36:55 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

void lexer_init(Lexer* lexer, char* input) {
	lexer->input = input;
	lexer->position = 0;
}

void lexer_skip_whitespace(Lexer* lexer) {
    while (ft_whitespace(lexer->input[lexer->position])) {
		lexer->position++;
    }
}

Token lexer_read_var(Lexer* lexer) {
    char* value = malloc(sizeof(char) * lexer->size);
    int i;

	i = 0;
    while (lexer->input[lexer->position])
	{
		if (ft_whitespace(lexer->input[lexer->position]))
			break;
        value[i++] = lexer->input[lexer->position++];
    }
    value[i] = '\0';

    Token token;
    token.value = value;
    free(value);
    return token;
}

Token lexer_next_token(Lexer* lexer) {
	
	lexer_skip_whitespace(lexer);
    char c_char = lexer->input[lexer->position];
	Token	token;
	
    if (c_char == '>') {
        token.value = ">";
    }
    else if (c_char == '<') {
        token.value = "<";
    }
    else if (c_char == '|') {
        token.value = "|";
    }
	else
   		return lexer_read_var(lexer);
	lexer->position++;
    return token;
}

int lexer_parsing(t_data *data)
{
	Lexer	lexer;
	Token	token;

	lexer_init(&lexer, data->input);
	lexer.size = ft_strlen(data->input);
	while (lexer.position < lexer.size)
	{
		token = lexer_next_token(&lexer);
		if (token.value[0] != 0)
			printf("TOKEN VAL : *%s*\n", token.value);
	}
	return (0);
}
