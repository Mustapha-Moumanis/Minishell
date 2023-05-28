/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elemlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:41:45 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/28 19:58:22 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_elem	*new_elem(char *content, enum e_type type, enum e_state state)
{
	t_elem	*node;

	node = malloc(sizeof(t_elem));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->state = state;
	node->next = NULL;
	return (node);
}

t_elem	*ft_last_elem(t_elem *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	addback_elem(t_elem **lst, t_elem *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_last_elem(*lst)->next = new;
}

void	ft_delone_elem(t_elem *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

void	ft_clear_elems(t_elem **lst, void (*del)(void *))
{
	t_elem	*tmp;

	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_delone_elem(*lst, del);
			*lst = tmp;
		}
	}
}
