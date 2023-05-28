/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:39:39 by shilal            #+#    #+#             */
/*   Updated: 2023/05/26 18:21:04 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize_(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	add_export(t_exprt **lst, t_exprt *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast_export(*lst)->next = new;
}

void	add_env(t_env **lst, t_env *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast_env(*lst)->next = new;
}
