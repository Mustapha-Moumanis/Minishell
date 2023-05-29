/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:56:13 by shilal            #+#    #+#             */
/*   Updated: 2023/05/24 17:01:40 by shilal           ###   ########.fr       */
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

void	ft_lenked_list(char **env, t_exec *val)
{
	char	*n;
	char	*v;
	int		i;

	i = -1;
	val->env = NULL;
	val->export = NULL;
	while (env[++i])
	{
		n = name(env[i]);
		v = value(env[i]);
		add_env(&val->env, new_env(n, v));
		add_export(&val->export, new_export(n, v, '\"'));
	}
	val->n_env = list_to_table_h(&val->env);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	str_lowercase(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
}
