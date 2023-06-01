/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:40:40 by shilal            #+#    #+#             */
/*   Updated: 2023/06/01 17:59:28 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**list_to_table_h(t_env **lst)
{
	t_env	*tmp;
	char	*s;
	char	**cmd;
	int		i;

	tmp = *lst;
	i = -1;
	cmd = ft_calloc((ft_lstsize_(*lst) + 1), sizeof(char **));
	if (!cmd)
		return (NULL);
	while (tmp)
	{
		s = ft_strjoin(tmp->name, "=");
		cmd[++i] = ft_strjoin(s, tmp->value);
		free(s);
		tmp = tmp->next;
	}
	return (cmd);
}

void	ft_remove_exp(t_exec *val, char *str)
{
	t_exprt	*t_exp;
	t_exprt	*tmp;

	t_exp = val->export;
	tmp = t_exp;
	if (t_exp && !ft_strcmp(t_exp->name, str))
	{
		val->export = val->export->next;
		free(t_exp);
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

int	unset_iscorect(t_exec *val, char *str)
{
	int	j;
	int	len;

	j = -1;
	len = ft_strlen(str);
	if (len == 0)
		return (unset_error(val->tmp->full_cmd[val->i]));
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (unset_error(val->tmp->full_cmd[val->i]));
	if (str[len - 1] == '+')
		len -= 1;
	while (++j < len)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (unset_error(val->tmp->full_cmd[val->i]));
	}
	return (1);
}

void	unset(t_exec *val)
{
	char		*str;

	val->i++;
	if (val->size == 1 && val->tmp->in_file >= 0)
	{
		while (val->tmp->full_cmd[val->i])
		{
			if (!unset_iscorect(val, val->tmp->full_cmd[val->i]))
				g_exit_status = 1;
			else
			{
				str = val->tmp->full_cmd[val->i];
				ft_remove_exp(val, str);
				ft_remove_env(val, str);
			}
			val->i++;
		}
		ft_double_free(val->n_env);
		val->n_env = list_to_table_h(&val->env);
	}
}
