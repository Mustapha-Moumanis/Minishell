/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:25:19 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/25 22:38:07 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_type(int type)
{
	switch (type)
	{
		case WORD: return "WORD";
		case WHITE_SPACE: return "WHITE_SPACE";
		case NEW_LINE: return "NEW_LINE";
		case QOUTE: return "QOUTE";
		case DQUOTE: return "DQUOTE";
		case ESCAPE: return "ESCAPE";
		case ENV: return "ENV";
		case PIPE_LINE: return "PIPE_LINE";
		case OR: return "OR";
		case REDIR_IN: return "REDIR_IN";
		case REDIR_OUT: return "REDIR_OUT";
		case HERE_DOC: return "HERE_DOC";
		case DREDIR_OUT: return "DREDIR_OUT";
	}
	return "NOT STRINGABLE";
}

char *get_state(int state)
{
	switch (state)
	{
		case IN_DQUOTE: return "IN_DQUOTE";
		case IN_QUOTE: return "IN_QUOTE";
		case GENERAL: return "GENERAL";
	}
	return "STATE INVALIDE";
}

void	print_list(t_elem **lst)
{
	t_elem	*tmp;

	if (lst)
	{
		printf("+---------+---------------------+-------+-----------------+----------------+\n");
		printf("|  index  |       content       |  len  |      state      |      type      |\n");
		printf("+---------+---------------------+-------+-----------------+----------------+\n");

		tmp = *lst;
		int index = 1;
		while (tmp)
		{
			printf("|%9d|%14s%7s|%4d%3s|%17s|%16s|\n", index, tmp->content, " ", tmp->len, " ", get_state(tmp->state), get_type(tmp->type));
			index++;
			tmp = tmp->next;
		}
		printf("+---------+---------------------+-------+-----------------+----------------+\n");
	}
}

char	*parse_line(t_data *data, t_elem *elem, char *str)
{
	char	*cmd;
	char	*tmp;

	while (elem)
	{
		if (elem->type == WORD || elem->type == 37 || elem->type == '\\')
			cmd = parse_word(&elem);
		// else if (elem->type == DQUOTE || elem->type == QOUTE)
		// {
		// 	cmd = parse_qoute(data, &elem, elem->type);
		// 	data->error = 1;
		// }
		else if (elem->type == ENV)
			cmd = parse_env(data, &elem);
		else
			cmd = ft_strdup(elem->content);
		tmp = str;
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if (cmd && elem->type != ENV)
			free(cmd);
		cmd = NULL;
		elem = elem->next;
	}
	tmp = str;
	str = ft_strjoin(tmp, "\n");
	free(tmp);
	return (str);
}

char	*update_line(t_data *last_data, char *str)
{
	t_data	data;
	char	*line;

	data = (t_data){0};
	data.n_env = last_data->n_env;
	data.input = str;
	lexer(&data);
	line = parse_line(&data, data.elem, ft_strdup(""));
	ft_clear_elems(&data.elem, &free);
	return (line);
}
