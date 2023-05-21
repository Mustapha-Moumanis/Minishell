/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 05:43:09 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/21 12:18:40 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	skeap_space(t_elem **t)
{
	while (*t && ((*t)->type == WHITE_SPACE))
		(*t) = (*t)->next;
}

int	print_synerror(char *content)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("\'\n", 2);
	return (1);
}

void	check_redirec(t_data *data, t_elem **t)
{
	(*t) = (*t)->next;
	skeap_space(t);
	if ((*t) && ((*t)->type == '|' || is_red((*t)->type) || (*t)->type == OR))
		data->error = print_synerror((*t)->content);
	else if (!(*t))
		data->error = print_synerror("newline");
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
			if ((*t)->state == GENERAL && (*t)->type == QOUTE)
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

void	syntax_errors(t_data *data)
{
	t_elem	*t;

	if (data->elem)
	{
		t = data->elem;
		skeap_space(&t);
		if (t && t->type == '|')
			data->error = print_synerror("|");
		while (t && data->error == 0)
		{
			if (t->state == GENERAL)
			{
				if (t->type == OR)
					data->error = print_synerror("||");
				if (is_red(t->type) || t->type == '|')
					check_redirec(data, &t);
				if (t && ft_quote(t->type))
					check_quote(data, &t);
			}
			if (t)
				t = t->next;
		}
	}
}
