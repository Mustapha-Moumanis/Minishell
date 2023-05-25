/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:59:18 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/25 13:48:36 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*change_content(t_data *data)
{
	char	*str;

	str = data->cmd_lst->next->content;
	free(data->cmd_lst->next);
	data->cmd_lst->next = NULL;
	return (str);
}

char	*collecting_cmd(t_data *data, t_elem **lex, char *str)
{
	char	*cmd;
	char	*tmp;

	skeap_space(lex);
	while (*lex && !ft_whitespace((*lex)->type) && (*lex)->type != '|')
	{
		cmd = parse_cmd(data, lex);
		tmp = str;
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if ((*lex)->type != ENV)
			free(cmd);
		if (str && (*lex)->next && is_red((*lex)->next->type))
		{
			ft_lstadd_back(&data->cmd_lst, ft_lstnew(str));
			str = NULL;
			break ;
		}
		(*lex) = (*lex)->next;
	}
	return (str);
}

void	get_red(t_data *data, t_elem **lex, enum e_type type, char	*str)
{
	if (str)
		ft_lstadd_back(&data->cmd_lst, ft_lstnew(str));
	str = ft_strdup("");
	(*lex) = (*lex)->next;
	if (type == HERE_DOC)
		her_doc(data, lex);
	else
	{
		str = collecting_cmd(data, lex, str);
		if (type == REDIR_IN)
			in_file(data, str);
		else if (type == REDIR_OUT)
			out_file(data, str);
		else if (type == DREDIR_OUT)
			dout_file(data, str);
	}
	free(str);
}

void	simple_cmd(t_data *data, t_elem **lex)
{
	char	*str;

	str = NULL;
	while (*lex && !((*lex)->type == '|' && (*lex)->state == GENERAL))
	{
		if ((*lex)->type == HERE_DOC || (is_red((*lex)->type) && !data->file_error))
			get_red(data, lex, (*lex)->type, str);
		else
		{
			if (!str && !ft_whitespace((*lex)->type))
				str = ft_strdup("");
			if (!(ft_whitespace((*lex)->type) && (*lex)->state == GENERAL))
				str = collecting_cmd(data, lex, str);
			if ((str && (!(*lex) || ft_whitespace((*lex)->type)))
				|| (*lex)->type == '|')
			{
				ft_lstadd_back(&data->cmd_lst, ft_lstnew(str));
				str = NULL;
			}
		}
		if ((*lex) && (*lex)->type == '|')
			break ;
		if (*lex)
			(*lex) = (*lex)->next;
	}
}

int	parsing(t_data *data, t_elem *lex)
{
	if (!lex)
		return (0);
	skeap_space(&lex);
	while (lex)
	{
		simple_cmd(data, &lex);
		if (!lex || lex->type == PIPE_LINE)
		{
			append_exution_struct(data);
			data->file_error = 0;
		}
		if (lex)
			lex = lex->next;
	}
	return (0);
}
