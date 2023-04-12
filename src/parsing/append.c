/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:12:07 by mmoumani          #+#    #+#             */
/*   Updated: 2023/04/12 23:51:26 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**list_to_table(t_list **lst)
{
	t_list	*tmp;
	char	**cmd;
	int		len;
	int		i;
	int		j;

	tmp = *lst;
	len = ft_lstsize(*lst);
	i = -1;
	cmd = ft_calloc((len + 1), sizeof(char *));
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		j = -1;
		cmd[++i] = ft_calloc(ft_strlen(tmp->content) + 1, sizeof(char));
		if (!cmd[i])
			return (ft_free(cmd, i));
		while (tmp->content[++j])
			cmd[i][j] = tmp->content[j];
		tmp = tmp->next;
	}
	return (cmd);
}

void	append_exution_struct(t_data *d)
{
	ft_lst_back(&d->head, ft_lst_new(d->in, d->out, list_to_table(&d->cmd_lst)));
	d->n_cmd = ft_lstsize(d->cmd_lst);
}
