/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:39:17 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/05 02:54:22 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define IN_FILE 1
#define OUT_FILE 3
#define PIPE 5
#define VAR 6
#define END 7



// int cat_var(t_data *data, char *str, char c)
// {
//    int     i;
//    int     j;

//    i = 0;
//    while (str[i] != c)
//        i++;
//    if (str[i] == '\0')
//        return (-1);
//    data->var = malloc(i);
//    j = 0;
//    while (j < i)
//    {
//        data->var[j] = str[j];
//        j++;
//    }
//    data->var[j] = '\0';
//    return (j);
// }


int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

void lexer_init(Lexer* lexer, char* input) {
	lexer->input = input;
	lexer->size = ft_strlen(input);
	lexer->position = 0;
}

void token_init(Token* token) {
	token->type = 0;
	token->value = "";
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
	token.type = VAR;
    token.value = value;
	lexer_skip_whitespace(lexer);
    free(value);
    return token;
}

Token lexer_next_token(Lexer* lexer) {
	
	lexer_skip_whitespace(lexer);
    char c_char = lexer->input[lexer->position];
	// printf("//%d//\n", lexer->position);
	Token	token;
	
    if (c_char == '>') {
		lexer->position++;
        token.value = ">";
		token.type = OUT_FILE;
    	return token;
    }
    else if (c_char == '<') {
		lexer->position++;
        token.value = "<";
		token.type = IN_FILE;
    	return token;
    }
    else if (c_char == '|') {
		lexer->position++;
        token.value = "|";
		token.type = PIPE;
    	return token;
    }
	else if (c_char && !ft_whitespace(c_char))
	{
   		return lexer_read_var(lexer);
	}
	else {
		token.type = END;
		token.value = "";
	}
	lexer->position++;
    return token;
}

int lexer_parsing(t_data *data)
{
	Lexer	lexer;
	Token	token;

	lexer_init(&lexer, data->input);
	token_init(&token);
	lexer.size = ft_strlen(data->input);
	while (token.type != END)
	{
		token = lexer_next_token(&lexer);
		printf("TOKEN VAL : *%s*\n", token.value);
		printf("TOKEN type : *%d*\n", token.type);
		// printf("TOKEN exer->position : *%d*\n", lexer.position);
		// break;
	}
	return (0);
}
