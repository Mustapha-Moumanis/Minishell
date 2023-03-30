/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:55:37 by mmoumani          #+#    #+#             */
/*   Updated: 2022/11/01 01:20:29 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_start(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!in(s2, s1[i]))
			return (i);
		i++;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *s2)
{
	int	l1;

	l1 = ft_strlen(s1);
	while (l1 - 1 >= 0)
	{
		if (!in(s2, s1[l1 - 1]))
			return (l1);
		l1--;
	}
	return (l1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	return (ft_substr(s1, start, end - start));
}
