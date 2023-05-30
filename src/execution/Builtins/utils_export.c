/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:59:36 by shilal            #+#    #+#             */
/*   Updated: 2023/05/30 18:13:38 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_export(t_exec *val)
{
	t_exprt	*tmp;

	tmp = val->export;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", val->tmp->out_file);
		ft_putstr_fd(tmp->name, val->tmp->out_file);
		if (tmp->value)
		{
			ft_putchar_fd('=', val->tmp->out_file);
			ft_putchar_fd(tmp->sep, val->tmp->out_file);
			ft_putstr_fd(tmp->value, val->tmp->out_file);
			ft_putchar_fd(tmp->sep, val->tmp->out_file);
		}
		ft_putstr_fd("\n", val->tmp->out_file);
		tmp = tmp->next;
	}
}

char	*my_strjoin_(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	if (!s1 && s2)
		return (ft_strdup(s2));
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	add_value_env(t_exec *val, char *n, char *v)
{
	t_env	*tmp;

	tmp = val->env;
	while (tmp)
	{
		if (!ft_strcmp(n, tmp->name))
		{
			free(tmp->value);
			tmp->value = v;
			free(n);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_env(&val->env, new_env(n, v));
}

void	ft_check_add(t_exec *val, char *n)
{
	t_exprt	*tmp;

	tmp = val->export;
	while (tmp)
	{
		if (!strcmp(tmp->name, n))
		{
			free(n);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_export(&val->export, new_export(n, NULL, '\0'));
}

int	all_iscorect(t_exec *val, char *str)
{
	int	j;
	int	len;

	j = -1;
	len = ft_strlen(str);
	if (len == 0)
		return (free(str), export_error(val->tmp->full_cmd[val->i]));
	if (ft_isdigit(str[0]))
		return (free(str), export_error(val->tmp->full_cmd[val->i]));
	if (str[len - 1] == '+')
		len -= 1;
	while (++j < len)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (free(str), export_error(val->tmp->full_cmd[val->i]));
	}
	return (1);
}
