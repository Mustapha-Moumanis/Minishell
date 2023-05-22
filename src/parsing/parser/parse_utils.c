/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:51:44 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/21 18:03:56 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*parce_qoute(t_data *data, t_elem **lex, enum e_type type)
{
	char	*s;
	char	*tmp;

	*lex = (*lex)->next;
	s = NULL;
	while (*lex)
	{
		if (!s)
			s = ft_strdup("");
		if ((*lex)->next && (*lex)->type == type && (*lex)->next->type == type)
			(*lex) = (*lex)->next;
		else if ((*lex)->type != type)
		{
			if ((*lex)->type == ENV)
				parse_env(data, lex);
			tmp = s;
			s = ft_strjoin(tmp, (*lex)->content);
			free(tmp);
		}
		else
			break ;
		if (*lex)
			*lex = (*lex)->next;
	}
	return (s);
}

char	*parse_word(t_elem **lex)
{
	char	*str;

	str = ft_strdup((*lex)->content);
	return (str);
}

char	*parse_env(t_data *data, t_elem **lex)
{
	char	*tmp;
	t_env	*env;

	tmp = (*lex)->content;
	env = data->n_env;
	while (env)
	{
		if (!ft_strcmp(tmp + 1, env->name))
		{
			(*lex)->content = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!env)
		(*lex)->content = ft_strdup("");
	free(tmp);
	return ((*lex)->content);
}

char	*parse_cmd(t_data *data, t_elem **lex)
{
	char	*cmd;

	cmd = NULL;
	if ((*lex))
	{
		if ((*lex)->type == WORD || (*lex)->type == EXIT_STATUS)
			cmd = parse_word(lex);
		else if ((*lex)->type == DQUOTE || (*lex)->type == QOUTE)
			cmd = parce_qoute(data, lex, (*lex)->type);
		else if ((*lex)->type == ENV)
			cmd = parse_env(data, lex);
	}
	return (cmd);
}
