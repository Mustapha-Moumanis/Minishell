/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:52:22 by mmoumani          #+#    #+#             */
/*   Updated: 2022/11/02 18:08:30 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nword(char const *s, char c)
{
	int	len;
	int	n;
	int	i;

	n = 0;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			n++;
		while (s[i] && (s[i] != c))
			i++;
		i++;
	}
	return (n);
}

static int	ft_lenword(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*ft_free(char **s, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	ft_skeep(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**s2;
	int		i;
	int		j;

	i = -1;
	if (!s)
		return (NULL);
	s2 = ft_calloc((ft_nword(s, c) + 1), sizeof(char *));
	if (!s2)
		return (NULL);
	while (*s)
	{
		s += ft_skeep(s, c);
		if ((*s != c) && *s)
		{
			j = 0;
			s2[++i] = ft_calloc(ft_lenword(s, c) + 1, sizeof(char));
			if (!s2[i])
				return (ft_free(s2, i));
			while (*s && *s != c)
				s2[i][j++] = *s++;
		}
	}
	return (s2);
}
