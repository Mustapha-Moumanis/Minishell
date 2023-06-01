/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:21:11 by mmoumani          #+#    #+#             */
/*   Updated: 2023/06/01 22:00:21 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_decremant_shlvl(t_exec *val)
{
	t_exprt	*tmp;
	char	*str;
	t_env	*env;
	int		j;

	tmp = val->export;
	env = val->env;
	while (tmp && env)
	{
		if (!ft_strcmp(tmp->name, "SHLVL"))
		{
			j = ft_atoi(tmp->value) - 1;
			free(tmp->value);
			str = ft_strdup(ft_itoa(j));
			tmp->value = str;
			env->value = str;
			break ;
		}
		tmp = tmp->next;
		env = env->next;
	}
	ft_double_free(val->n_env);
	val->n_env = list_to_table_h(&val->env);
}

int	parser(t_data *data, t_exec *val)
{
	data->input = readline("minishell : ");
	if (!data->input)
	{
		ft_decremant_shlvl(val);
		rl_clear_history();
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(data->input) > 0)
		add_history(data->input);
	lexer(data);
	syntax_errors(data, data->elem);
	if (data->error == 0)
		parsing(data, data->elem);
	ft_clear_elems(&data->elem, &free);
	free(data->input);
	return (data->error);
}
