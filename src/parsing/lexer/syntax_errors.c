/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 05:43:09 by mmoumani          #+#    #+#             */
/*   Updated: 2023/06/04 14:30:24 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	print_synerror(char *content)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("\'\n", 2);
	return (1);
}

void	check_redirec_pipe(t_data *data, t_elem **t, enum e_type type)
{
	if (type == OR)
		data->error = print_synerror("||");
	else
	{
		(*t) = (*t)->next;
		skeap_space(t);
		if (*t)
		{
			if (is_red(type) && ((*t)->type == '|'
					|| is_red((*t)->type) || (*t)->type == OR))
				data->error = print_synerror((*t)->content);
			else if (type == '|' && ((*t)->type == '|' || (*t)->type == OR))
				data->error = print_synerror((*t)->content);
		}
		else
			data->error = print_synerror("newline");
	}
}

void	check_quote(t_data *data, t_elem **t)
{
	int	q;
	int	dq;

	q = 0;
	dq = 0;
	while (*t)
	{
		skeap_space(t);
		if ((*t))
		{
			if ((*t)->state == GENERAL && (*t)->type == QUOTE)
				q++;
			else if ((*t)->state == GENERAL && (*t)->type == DQUOTE)
				dq++;
			(*t) = (*t)->next;
		}
	}
	if ((q > 0 && q % 2 == 1) || (dq > 0 && dq % 2 == 1))
	{
		ft_putstr_fd("Missing closing quote!!\n", 2);
		data->error = 1;
	}
}

void	first_check(t_data *data, t_elem *t)
{
	int	count;

	count = 0;
	while (t && data->error == 0)
	{
		if (t->state == GENERAL && t->type == AND)
			data->error = print_synerror(t->content);
		if (t->state == GENERAL && t->type == HERE_DOC)
			count++;
		t = t->next;
	}
	if (count > 16)
	{
		ft_putendl_fd("Error: maximum here-document count exceeded", 2);
		exit(2);
	}
}

void	syntax_errors(t_data *data, t_elem	*t)
{
	if (!t)
		return ;
	skeap_space(&t);
	first_check(data, data->elem);
	if (t && t->type == '|')
		data->error = print_synerror("|");
	while (t && data->error == 0)
	{
		if (t->state == GENERAL)
		{
			if (is_red(t->type) || t->type == '|' || t->type == OR)
				check_redirec_pipe(data, &t, t->type);
			if (t && ft_quote(t->type))
				check_quote(data, &t);
		}
		if (t)
			t = t->next;
	}
}
