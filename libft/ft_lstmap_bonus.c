/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:59:06 by mmoumani          #+#    #+#             */
/*   Updated: 2022/11/05 04:13:56 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cplst;
	t_list	*node;
	void	*content;

	if (!lst)
		return (NULL);
	if (!f || !del)
		return (lst);
	cplst = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			if (content)
				del(content);
			ft_lstclear(&cplst, del);
			return (0);
		}
		ft_lstadd_back(&cplst, node);
		lst = lst->next;
	}
	return (cplst);
}
