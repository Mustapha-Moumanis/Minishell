/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:26:25 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/05 22:50:27 by mmoumani         ###   ########.fr       */
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
#define TOKEN_OUT_FILE 3
#define TOKEN_PIPE 5
#define TOKEN_VAR 6
#define TOKEN_ERROR 7
#define TOKEN_END 99

int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

// int    cat_var(t_data *data, char *str, char c)
// {
//     int     i;
//     int     j;

//     i = 0;
//     while (str[i] && str[i] != c)
//         i++;
//     if (str[i] == '\0')
//         return (-1);
//     data->var = malloc(i);
//     j = 0;
//     while (j < i)
//     {
//         data->var[j] = str[j];
//         j++;
//     }
//     data->var[j] = '\0';
//     return (j);
// }

// functions help 

void lexer_init(Lexer* lexer, char* input) {
	lexer->input = input;
	lexer->size = strlen(input);
	lexer->position = 0;
}

// void token_init(Token* token) {
// 	token->type = 0;
// 	token->value = "";
// }

void lexer_skip_whitespace(Lexer* lexer) {
    while (ft_whitespace(lexer->input[lexer->position])) {
		lexer->position++;
    }
}

int    cat_var(Token *token, char *str, char c)
{
    char*   value;
    int     i;
    int     j;
    

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    if (str[i] == '\0')
    {
        token->value = NULL;
        token->type = TOKEN_END;
        return (-1);
    }
    value = malloc(sizeof(char) * i);
    j = 0;
    while (j < i)
    {
        value[j] = str[j];
        j++;
    }
    value[j] = '\0';
    token->value = value;
    printf("var %c\n", str[j]);
	token->type = TOKEN_VAR;
    return (i + 1);
}

// void    cat_var(Lexer* lexer, Token *token)
// {
//     char*   value;
//     char    break_char;
//     int     i;

//     value = malloc(sizeof(char) * lexer->size);
//     break_char = lexer->input[lexer->position++];
//     i = 0;
//     while (lexer->input[i] == break_char)
//         i++;
//     if (lexer->input[i] == '\0')
//     {
//         token->type = TOKEN_END;
//         token->value = "";
//     }
//     while (lexer->input[lexer->position] != break_char)
//         value[i++] = lexer->input[lexer->position++];
//     value[i] = '\0';
//     lexer->position++;
//     token->type = TOKEN_VAR;
//     token->value = value;
//     free(value);
// }

void	lexer_read_var(Lexer* lexer, Token *token) 
{
    // char c_char = lexer->input[lexer->position];
    int i = cat_var(token, lexer->input + lexer->position, lexer->input[lexer->position - 1]);
    lexer->position++;
    if (i != -1)
    {
        lexer->position += i;
        printf("var 2 %c\n", lexer->input[lexer->position]);

    }
    else
        printf("ERROR\n");
    // cat_var(lexer, token);
}

// Tokenize the input string
void lexer_next_token(Lexer* lexer, Token *token) 
{
    lexer_skip_whitespace(lexer);

    char c_char = lexer->input[lexer->position];

    if (c_char == '>') {
		lexer->position++;
        token->value = ">";
		token->type = TOKEN_OUT_FILE;
    }
    else if (c_char == '<') {
		lexer->position++;
        token->value = "<";
		token->type = TOKEN_IN_FILE;
    }
    else if (c_char == '|') {
		lexer->position++;
        token->value = "|";
		token->type = TOKEN_PIPE;
    }
    else if (c_char == '\"' || c_char == '\''){
		lexer->position++;
        lexer_read_var(lexer, token);
    }
    else if (c_char == '\0'){
        token->type = TOKEN_END;
        token->value = "";
    }
    else {
        printf("*%c*\n", lexer->input[lexer->position]);
		lexer->position++;
        // lexer_read_var(lexer, token);
    }
}

// Free the memory allocated for a token's value string
void token_free(Token* token) {
    free(token->value);
}

int main() {
    Lexer lexer;
    // int i = 0;
    lexer_init(&lexer, "< \"file ls -la\" | >file");


    Token token;
    while (token.type != TOKEN_END)
    // while (i < lexer.size)
    {
        lexer_next_token(&lexer, &token);
        if (token.type == TOKEN_OUT_FILE)
            printf("TOKEN_OUT_FILE %s\n", token.value);
        else if (token.type == TOKEN_IN_FILE)
            printf("TOKEN_IN_FILE %s\n", token.value);
        else if (token.type == TOKEN_PIPE)
            printf("TOKEN_PIPE %s\n", token.value);
        else if (token.type == TOKEN_VAR)
            printf("TOKEN_VAR %s\n", token.value);
        else if (token.type == TOKEN_ERROR)
            printf("TOKEN_ERROR %s\n", token.value);
        else if (token.type == TOKEN_END)
            printf("TOKEN_END\n");
        // i++;
        // lexer.position += 1;
    }
    return 0;
}
