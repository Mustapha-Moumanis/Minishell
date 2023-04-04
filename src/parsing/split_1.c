/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 06:36:16 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/04 22:02:08 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// <file1 ls -la | wc -l > file2

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define token types as constants
#define TOKEN_INTEGER 1
#define TOKEN_PLUS 2
#define TOKEN_MINUS 3
#define TOKEN_MULTIPLY 4
#define TOKEN_DIVIDE 5
#define TOKEN_LPAREN 6
#define TOKEN_RPAREN 7
#define TOKEN_END 8

struct Token {
    int type;
    char* value;
};

struct Lexer {
    char* input;
    int position;
};

void lexer_init(struct Lexer* lexer, char* input) {
    lexer->input = input;
    lexer->position = 0;
}

// Return the character at the current position of the lexer
char lexer_peek(struct Lexer* lexer) {
    return lexer->input[lexer->position];
}

// Advance the position of the lexer by one and return the new character
char lexer_advance(struct Lexer* lexer) {
    lexer->position++;
    return lexer_peek(lexer);
}

// Skip any whitespace characters in the input string
void lexer_skip_whitespace(struct Lexer* lexer) {
    while (isspace(lexer_peek(lexer))) {
        lexer_advance(lexer);
    }
}

// Read an integer value from the input string
struct Token lexer_read_integer(struct Lexer* lexer) {
    char* value = malloc(sizeof(char) * 10);
    int i = 0;
    while (isdigit(lexer_peek(lexer))) {
        value[i++] = lexer_advance(lexer);
    }
    value[i] = '\0';

    struct Token token;
    token.type = TOKEN_INTEGER;
    token.value = value;
    free(value);
    return token;
}

// Tokenize the input string
struct Token lexer_next_token(struct Lexer* lexer) {
    lexer_skip_whitespace(lexer);

    char current_char = lexer_peek(lexer);

    if (isdigit(current_char)) {
        return lexer_read_integer(lexer);
    }

    if (current_char == '+') {
        lexer_advance(lexer);
        struct Token token;
        token.type = TOKEN_PLUS;
        token.value = "+";
        return token;
    }

    if (current_char == '-') {
        lexer_advance(lexer);
        struct Token token;
        token.type = TOKEN_MINUS;
        token.value = "-";
        return token;
    }

    if (current_char == '*') {
        lexer_advance(lexer);
        struct Token token;
        token.type = TOKEN_MULTIPLY;
        token.value = "*";
        return token;
    }

    if (current_char == '/') {
        lexer_advance(lexer);
        struct Token token;
        token.type = TOKEN_DIVIDE;
        token.value = "/";
        return token;
    }

    if (current_char == '(') {
        lexer_advance(lexer);
        struct Token token;
        token.type = TOKEN_LPAREN;
        token.value = "(";
        return token;
    }

    if (current_char == ')') {
        lexer_advance(lexer);
        struct Token token;
        token.type = TOKEN_RPAREN;
        token.value = ")";
        return token;
    }

    struct Token token;
    token.type = TOKEN_END;
    token.value = "";
    return token;
}

// Free the memory allocated for a token's value string
void token_free(struct Token* token) {
    free(token->value);
}

int main() {
    struct Lexer lexer;
    lexer_init(&lexer, " ");


    struct Token token;
    while (token.type != TOKEN_END)
    {
        token = lexer_next_token(&lexer);
        if (token.type == TOKEN_INTEGER)
            printf("TOKEN_INTEGER %s\n", token.value);
        else if (token.type == TOKEN_PLUS)
            printf("TOKEN_PLUS %s\n", token.value);
        else if (token.type == TOKEN_MINUS)
            printf("TOKEN_MINUS %s\n", token.value);
        else if (token.type == TOKEN_MULTIPLY)
            printf("TOKEN_MULTIPLY %s\n", token.value);
        else if (token.type == TOKEN_DIVIDE)
            printf("TOKEN_DIVIDE %s\n", token.value);
        else if (token.type == TOKEN_LPAREN)
            printf("TOKEN_LPAREN %s\n", token.value);
        else if (token.type == TOKEN_RPAREN)
            printf("TOKEN_RPAREN %s\n", token.value);
        else if (token.type == TOKEN_END)
            printf("TOKEN_END\n");
    }
    return 0;
}
