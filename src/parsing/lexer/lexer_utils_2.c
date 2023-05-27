/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:32:42 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/27 17:36:13 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

void	get_and(t_lexer *lexer, t_token *token)
{
	char	*value;

	value = ft_strdup("&");
	if (lexer->input[lexer->position + 1] == '&')
	{
		free(value);
		value = ft_strdup("&&");
	}
	token->type = AND;
	token->value = value;
	lexer->position += ft_strlen(value);
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
