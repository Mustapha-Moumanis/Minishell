/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:23:24 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/23 11:07:02 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_red(int c)
{
	return (c == '>' || c == '<' || c == HERE_DOC || c == DREDIR_OUT);
}

int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_quote(int c)
{
	return (c == '\"' || c == '\'');
}

int	special_char(char c)
{
	return (ft_quote(c) || is_red(c) || c == '|' || c == '$' || c == '\\');
}

char	*cat_var(char *str, int nb)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	if (nb)
	{
		if (ft_isdigit(str[0]))
			i = 1;
		else
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
	}
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
