/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:04:39 by shilal            #+#    #+#             */
/*   Updated: 2023/05/08 05:26:10 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_export	*new_export(char *name, char *value, char sep)
{
	t_export	*node;

	node = malloc(sizeof(t_export));
	if (!node)
		return (NULL);
	node->name = name;
	node->sep = sep;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_env(t_env **lst, t_env *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast_env(*lst)->next = new;
}

t_export	*ft_lstlast_export(t_export *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
