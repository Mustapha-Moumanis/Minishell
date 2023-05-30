/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:32:42 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/30 23:31:08 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	get_word(t_lexer *lexer, t_token *token)
{
	char	*value;

	value = cat_var(lexer->input + lexer->position, 0);
	lexer->position += ft_strlen(value);
	token->value = value;
	token->type = WORD;
}

char	*env_advance(t_token *token, char advance)
{
	char	*value;

	if (advance == '$')
		value = ft_strdup("$$");
	else
		value = ft_strdup("$");
	token->type = WORD;
	return (value);
}

void	get_env(t_lexer *lexer, t_token *token, char first, char advance)
{
	char	*str;
	char	*value;

	if (!advance || ft_whitespace(advance) || advance == '$'
		|| (special_char(advance) && !ft_quote(advance)))
		value = env_advance(token, advance);
	else if (advance == '?')
	{
		value = ft_strdup("$?");
		token->type = EXIT_STATUS;
	}
	else
	{
		str = cat_var(lexer->input + lexer->position + 1, 1);
		value = ft_strjoin("$", str);
		token->type = first;
		free(str);
	}
	token->value = value;
	lexer->position += ft_strlen(value);
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
	token->type = c;
	return (1);
}
