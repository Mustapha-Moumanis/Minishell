/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:26:25 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/07 02:51:16 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// <file1 ls -la | wc -l > file2

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define token types as constants
#define TOKEN_IN_FILE 1
#define TOKEN_OUT_FILE 2
#define TOKEN_PIPE 3
#define TOKEN_COMMAND 4
#define TOKEN_ERROR 5
#define TOKEN_END 99

int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

void lexer_init(Lexer* lexer, char* input) {
	lexer->input = input;
	lexer->size = ft_strlen(input);
	lexer->position = 0;
}

void lexer_skip_whitespace(Lexer* lexer) {
	while (ft_whitespace(lexer->input[lexer->position])) {
		lexer->position++;
	}
}

char	*cat_var(char *str, char c)
{
	char*   value;
	int     i;
	int     j;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (NULL);
	value = malloc(sizeof(char) * i);
	j = 0;
	while (j < i)
	{
		value[j] = str[j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	lexer_read_cmd_quote(Lexer* lexer, Token *token) 
{
	char	c_char = lexer->input[lexer->position - 1];
	char	*value = cat_var(lexer->input + lexer->position, c_char);
	lexer->position++;
	if (value != NULL)
	{
		lexer->position += ft_strlen(value);
		token->value = value;
		token->type = TOKEN_COMMAND;
	}
	else
	{
		token->value = NULL;
		token->type = TOKEN_END;
	}
    free(value);
}

char	*cat_var_2(char *str)
{
    char	*value;
    int     i;
    int     j;

    i = 0;
    while (str[i] && !(ft_whitespace(str[i])))
        i++;
    value = malloc(sizeof(char) * (i + 1));
    j = -1;
    while (++j < i)
        value[j] = str[j];
    value[j] = '\0';
	return (value);
}

void	lexer_read_cmd(Lexer* lexer, Token *token) 
{
	char	*value = cat_var_2(lexer->input + lexer->position);
	if (value != NULL)
	{
		lexer->position += ft_strlen(value);
		token->value = value;
		token->type = TOKEN_COMMAND;
	}
	else
	{
		token->value = NULL;
		token->type = TOKEN_END;
	}
    free(value);
}

void	lexer_check_token(Lexer* lexer, Token *token, char c_char)
{
	if (c_char == '\"' || c_char == '\''){
		lexer->position++;
		lexer_read_cmd_quote(lexer, token);
	}
	else if (c_char == '\0' || c_char == '\n'){
		token->type = TOKEN_END;
		token->value = "";
	}
	else
		lexer_read_cmd(lexer, token);		
}

void	lexer_next_token(Lexer* lexer, Token *token)
{
	char c_char = lexer->input[lexer->position];
	lexer_skip_whitespace(lexer);

	if (c_char == '>')
	{
		lexer->position++;
		lexer_check_token(lexer, token, c_char);
		token->type = TOKEN_OUT_FILE;
	}
    else if (c_char == '<')
	{
		lexer->position++;
		lexer_check_token(lexer, token, c_char);
		token->type = TOKEN_IN_FILE;
	}
	else if (c_char == '|') {
		lexer->position++;
		token->value = "|";
		token->type = TOKEN_PIPE;
	}
	else
		lexer_check_token(lexer, token, c_char);
	// else if (c_char == '\"' || c_char == '\''){
	// 	lexer->position++;
	// 	lexer_read_cmd_quote(lexer, token);
	// }
	// else if (c_char == '\0'){
	// 	token->type = TOKEN_END;
	// 	token->value = "";
	// }
	// else
	// {
	// 	lexer_read_cmd(lexer, token);		
	// }
        // ft_cmd(lexer, token);
}

void	lexer(t_data *data)
{
	Lexer	lexer;
	Token	token;
	
	lexer_init(&lexer, data->input);
	while (token.type != TOKEN_END)
	{
		lexer_next_token(&lexer, &token);
		if (token.type == TOKEN_OUT_FILE)
			printf("TOKEN_OUT_FILE %s\n", token.value);
		else if (token.type == TOKEN_IN_FILE)
			printf("TOKEN_IN_FILE %s\n", token.value);
		else if (token.type == TOKEN_PIPE)
			printf("TOKEN_PIPE %s\n", token.value);
		else if (token.type == TOKEN_COMMAND)
			printf("TOKEN_COMMAND %s\n", token.value);
		else if (token.type == TOKEN_ERROR)
			printf("TOKEN_ERROR %s\n", token.value);
		else if (token.type == TOKEN_END)
			printf("TOKEN_END\n");
	}
}
