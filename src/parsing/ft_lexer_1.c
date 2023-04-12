/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:55:38 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/12 20:54:25 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cat_var(char *str, char c)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (NULL);
	value = malloc(sizeof(char) * i);
	j = -1;
	while (++j < i)
		value[j] = str[j];
	value[j] = '\0';
	return (value);
}

void	lexer_read_cmd_quote(t_lexer *lexer, t_token *token)
{
	char	c_char;
	char	*value;

	c_char = lexer->input[lexer->position - 1];
	value = cat_var(lexer->input + lexer->position, c_char);
	lexer->position++;
	if (value != NULL)
	{
		lexer->position += ft_strlen(value);
		token->value = value;
		token->type = TOKEN_COMMAND;
	}
	else
	{
		token->type = TOKEN_END;
	}
}

char	*cat_var_2(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (str[i] && !(ft_whitespace(str[i])) && str[i] != '|' && str[i] != '<' && str[i] != '>')
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

void	check_lexer_error(t_lexer *lexer)
{
	char c;
	char n_c;

	c = lexer->input[lexer->position];
	n_c = lexer->input[lexer->position + 1];
	if (c == 0)
		ft_putstr_fd("syntax error near unexpected token `newline\'\n", 2);
	else if (c == '>' && n_c == '>')
		ft_putstr_fd("syntax error near unexpected token `>>\'\n", 2);
	else if (c == '>')
		ft_putstr_fd("syntax error near unexpected token `>\'\n", 2);
	else if (c == '<' && n_c == '<')
		ft_putstr_fd("syntax error near unexpected token `<<\'\n", 2);
	else if (c == '<')
		ft_putstr_fd("syntax error near unexpected token `<\'\n", 2);
	lexer->error = 1;
}

void	lexer_read_cmd(t_lexer *lexer, t_token *token)
{
	char	*value;

	value = cat_var_2(lexer->input + lexer->position);
	if (value != NULL && value[0] != 0)
	{
		lexer->position += ft_strlen(value);
		token->value = value;
		token->type = TOKEN_COMMAND;
	}
	else
	{
		check_lexer_error(lexer);
		// if (lexer->input[lexer->position] == 0)
		// 	printf("syntax error near unexpected token `newline`\n");
		// else if (lexer->input[lexer->position] == '>')
		// 	printf("syntax error near unexpected token `>`\n");
		// lexer->error = 1;
		token->type = TOKEN_END;
	}
	free(value);
}
