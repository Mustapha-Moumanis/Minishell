/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:04:49 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/19 17:22:08 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**change_to_table(t_list **lst)
{
	char	**cmd;
	t_list	*tmp;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (ft_lstsize(*lst) + 1));
	if (!cmd)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		cmd[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	append_exution_struct(t_data *d)
{
	ft_cmd_back(&d->head, ft_new_cmd(d->in, d->out, change_to_table(&d->cmd_lst)));
	d->n_cmd = ft_lstsize(d->cmd_lst);
	ft_lstclear(&d->cmd_lst, &free);
	init_parssing_data(d);
}
