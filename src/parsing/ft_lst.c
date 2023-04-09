/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:41:45 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/08 03:00:39 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_lst_new(char **in_file, char **out_file, char **full_cmd)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->in_file = in_file;
	node->out_file = out_file;
	node->full_cmd = full_cmd;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_lst_last(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}


void	ft_lst_back(t_cmd **lst, t_cmd *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lst_last(*lst)->next = new;
}
