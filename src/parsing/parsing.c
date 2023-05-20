/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:59:18 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/20 14:43:28 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*change_content(t_data *data)
{
	char	*str;

	str = data->cmd_lst->next->content;
	free(data->cmd_lst->next);
	data->cmd_lst->next = NULL;
	return (str);
}

void	echo_cmd(t_data *data, t_elem **lex)
{
	char	*str;
	char	*tmp;
	char	*cmd;

	str = NULL;
	skeap_space(lex);
	if (ft_strcmp(data->cmd_lst->next->content, "-n"))
		str = change_content(data);
	while (*lex && !((*lex)->type == '|' && (*lex)->state == GENERAL))
	{
		if (!str)
			str = ft_strdup("");
		tmp = str;
		cmd = parse_cmd(lex);
		if (!cmd)
		{
			cmd = ft_strdup(" ");
			while (*lex && (*lex)->next && (ft_whitespace((*lex)->type)) && (ft_whitespace((*lex)->next->type)))
				(*lex) = (*lex)->next;
		}
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		free(cmd);
		if (*lex)
			(*lex) = (*lex)->next;
	}
	ft_lstadd_back(&data->cmd_lst, ft_lstnew(str));
}

char	*collecting_cmd(t_data *data, t_elem **lex, char *str)
{
	char	*cmd;
	char	*tmp;

	skeap_space(lex);
	while (*lex && !ft_whitespace((*lex)->type))
	{
		cmd = parse_cmd(lex);
		tmp = str;
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		if ((*lex)->type != ENV)
			free(cmd);
		if (str && (*lex)->next && is_red((*lex)->next->type))
		{
			ft_lstadd_back(&data->cmd_lst, ft_lstnew(str));
			str = NULL;
			break; 
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
	str = collecting_cmd(data, lex, str);
	if (type == REDIR_IN)
		in_file(data, str);
	else if (type == REDIR_OUT)
		out_file(data, str);
	else if (type == DREDIR_OUT)
		dout_file(data, str);
	free(str);
}

void	simple_cmd(t_data *data, t_elem **lex)
{
	char	*str;

	str = NULL;
	while (*lex && !((*lex)->type == '|' && (*lex)->state == GENERAL))
	{
		if (is_red((*lex)->type))
			get_red(data, lex, (*lex)->type, str);
		else
		{
			if (!str && !ft_whitespace((*lex)->type))
				str = ft_strdup("");
			if (!(ft_whitespace((*lex)->type) && (*lex)->state == GENERAL))
				str = collecting_cmd(data, lex, str);
			if ((str && (!(*lex) || ft_whitespace((*lex)->type))))
			{
				ft_lstadd_back(&data->cmd_lst, ft_lstnew(str));
				str = NULL;
			}
		}
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
			append_exution_struct(data);
		if (lex)
			lex = lex->next;
	}
	return (0);
}
