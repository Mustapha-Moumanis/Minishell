/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:39:39 by shilal            #+#    #+#             */
/*   Updated: 2023/06/01 17:47:06 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*name(char *str)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	while (++j < i)
		name[j] = str[j];
	name[j] = '\0';
	return (name);
}

char	*value(char *str)
{
	char	*value;
	int		i;
	int		j;
	int		f;

	i = 0;
	j = 0;
	while (str[j] != '=')
		j++;
	f = j + 1;
	while (str[j++])
		i++;
	j = f;
	value = malloc(i + 1);
	if (!value)
		return (NULL);
	f = -1;
	while (++f < i)
		value[f] = str[j++];
	value[f] = '\0';
	return (value);
}

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
