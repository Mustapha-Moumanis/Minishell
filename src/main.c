/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:31:41 by shilal            #+#    #+#             */
/*   Updated: 2023/04/12 23:57:25 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_double_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}


int main(int ac, char **av, char **env)
{
	t_data data;

	while (1337)
	{
		data = (t_data){0};
		data.ac = ac;
		data.av = av;
		data.env = env;
		parser(&data);
		// exuct(data);
		int i = -1;
		while (data.head->full_cmd[++i])
			printf("*%s*\n", data.head->full_cmd[i]);
		if (data.head->next)
		{
			i = -1;
			while (data.head->next->full_cmd[++i])
				printf("*%s*\n", data.head->next->full_cmd[i]);
		}
		printf("in_file : %d\n", data.head->in_file);
		printf("out_file : %d\n", data.head->out_file);
		
		ft_lst_clear(&data.head, &ft_double_free);
		ft_lstclear(&data.cmd_lst, &free);
		// system("leaks minishell");
	}
}
