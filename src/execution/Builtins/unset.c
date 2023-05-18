/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:40:40 by shilal            #+#    #+#             */
/*   Updated: 2023/05/18 09:22:06 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

char	**list_to_table_h(t_env **lst)
{
	t_env	*tmp;
	char	*s;
	char	**cmd;
	int		len;
	int		i;

	tmp = *lst;
	i = -1;
	cmd = ft_calloc((ft_lstsize_(*lst) + 1), sizeof(char *));
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		len = ft_strlen(tmp->name) + ft_strlen(tmp->value) + 1;
		s = ft_strjoin(tmp->name, "=");
		cmd[++i] = ft_strjoin(s, tmp->value);
		free(s);
		tmp = tmp->next;
	}
	return (cmd);
}

void	ft_remove_exp(t_exec *val, char *str)
{
	t_export	*t_exp;
	t_export	*tmp;

	t_exp = val->export;
	tmp = t_exp;
	if (t_exp && !ft_strcmp(t_exp->name, str))
	{
		val->export = val->export->next;
		free(tmp);
		return ;
	}
	while (t_exp && t_exp->next)
	{
		if (!ft_strcmp(t_exp->next->name, str))
		{
			tmp = t_exp->next;
			t_exp->next = t_exp->next->next;
			if (!tmp->value)
				free(tmp->name);
			free(tmp);
			break ;
		}
		t_exp = t_exp->next;
	}
}

int	ft_remove_env(t_exec *val, char *s)
{
	t_env	*tm_env;
	t_env	*tmp;

	tm_env = val->env;
	while (tm_env && tm_env->next)
	{
		if (!ft_strcmp(tm_env->name, s) || !ft_strcmp(tm_env->next->name, s))
		{
			tmp = tm_env->next;
			if (!ft_strcmp(tm_env->name, s))
			{
				tmp = tm_env;
				val->env = val->env->next;
			}
			else
				tm_env->next = tm_env->next->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return (1);
		}
		tm_env = tm_env->next;
	}
	return (0);
}

void	unset(t_exec *val)
{
	char		*str;

	val->i++;
	while (val->tmp->full_cmd[val->i])
	{
		str = val->tmp->full_cmd[val->i];
		ft_remove_exp(val, str);
		if (ft_remove_env(val, str))
		{
			ft_double_free(val->n_env);
			val->n_env = list_to_table_h(&val->env);
		}
		val->i++;
	}
}
